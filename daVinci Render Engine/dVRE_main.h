#pragma once

#include "dVRE_window.h"
#include "dVRE_pipeline.h"
#include "dVRE_device.h"
#include "dVRE_swapchain.h"

//std lib
#include <memory>
#include <vector>

namespace dVRE {
	class MainApp {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			MainApp();
			~MainApp();

			MainApp(const MainApp&) = delete;
			MainApp& operator=(const MainApp&) = delete;

			void run();

		private:
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			dVREwindow dvreWindow{WIDTH, HEIGHT, "Project: Ordus"};
			dVREdevice dvreDevice{dvreWindow};
			dVRESwapChain dvreSwapchain{ dvreDevice, dvreWindow.getExtent() };
			std::unique_ptr<dVREpipeline> dvrePipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
	};
}//namespace dVRE