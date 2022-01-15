#include "dVRE_main.h"

namespace dVRE {

	void Main::run() {
		while (!dVREwindow.shouldClose()) {
			glfwPollEvents();
		}
	}
}//namespace dVRE