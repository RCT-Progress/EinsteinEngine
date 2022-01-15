#include "dVRE_window.h"

namespace dVRE {

	dVREwindow::dVREwindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	}

	dVREwindow::~dVREwindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void dVREwindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
} //namespace dVRE