#pragma once

#include "dVRE_window.h"

namespace dVRE {
	class Main {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			void run();

		private:
			dVREwindow dVREwindow{WIDTH, HEIGHT, "Project: Ordus"};
	};
}