#pragma once

#include "dVRE_device.h"

//std
#include <string>
#include <vector>

namespace dVRE {

	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class dVREpipeline {
		public:
			dVREpipeline(dVREdevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);
			~dVREpipeline();

			dVREpipeline(const dVREpipeline&) = delete;
			void operator=(const dVREpipeline&) = delete;

			void bind(VkCommandBuffer commandBuffer);				 

			static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo, uint32_t width, uint32_t height);

	    private:
			static std::vector<char> readFile(const std::string& filepath);

			void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);

			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			dVREdevice& dvreDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;
	};
}