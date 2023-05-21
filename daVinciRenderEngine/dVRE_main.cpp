#include "dVRE_main.h"

//std lib
#include <stdexcept>
#include <array>

namespace dVRE {

	MainApp::MainApp() {
		loadmodels();
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	MainApp::~MainApp() {

		vkDestroyPipelineLayout(dvreDevice.device(), pipelineLayout, nullptr);
	}

	void MainApp::run() {

		while (!dvreWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}
	}

	void MainApp::loadmodels() {
		std::vector<dVREmodel::Vertex> vertices{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		dVREModel = std::make_unique<dVREmodel>(dvreDevice, vertices);
	}

	void MainApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(dvreDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void MainApp::createPipeline() {

		PipelineConfigInfo pipelineConfig{};
		dVREpipeline::defaultPipelineConfigInfo(pipelineConfig, dvreSwapchain.width(), dvreSwapchain.height());
		pipelineConfig.renderPass = dvreSwapchain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		dvrePipeline = std::make_unique<dVREpipeline>(dvreDevice, "daVinciRenderEngine/shaders/shader.vert.spv", "daVinciRenderEngine/shaders/shader.frag.spv", pipelineConfig);
	}

	void MainApp::createCommandBuffers(){

		commandBuffers.resize(dvreSwapchain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = dvreDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(dvreDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (int i = 0; i < commandBuffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffers!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = dvreSwapchain.getRenderPass();
			renderPassInfo.framebuffer = dvreSwapchain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = { 0,0 };
			renderPassInfo.renderArea.extent = dvreSwapchain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			dvrePipeline->bind(commandBuffers[i]);
			dVREModel->bind(commandBuffers[i]);
			dVREModel->draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to record command buffer!");
			}
		}
	}
	void MainApp::drawFrame(){
	uint32_t imageIndex;
	auto result = dvreSwapchain.acquireNextImage(&imageIndex);
	 if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire next swap chain image!");
	}

	 result = dvreSwapchain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
}

}//namespace dVRE