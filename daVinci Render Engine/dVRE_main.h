#pragma once

#include "dVRE_window.h"
#include "dVRE_pipeline.h"
#include "dVRE_device.h"

namespace dVRE {
	class Main {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			void run();

		private:
			dVREwindow dVREwindow{WIDTH, HEIGHT, "Project: Ordus"};
			dVREdevice dvreDevice{dVREwindow};
			dVREpipeline dVREpipeline{dvreDevice, "shaders/shader.vert.spv", "shaders/shader.vert.spv", dVREpipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}//namespace dVRE