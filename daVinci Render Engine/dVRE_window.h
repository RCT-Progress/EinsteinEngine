#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace dVRE {

	class dVREwindow {

		public:
			dVREwindow(int w, int h, std::string name);
			~dVREwindow();

			dVREwindow(const dVREwindow&) = delete;
			dVREwindow& operator=(const dVREwindow&) = delete;

			bool shouldClose() { return glfwWindowShouldClose(window); }

			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

		private:

			void initWindow();

			const int width;
			const int height;

			std::string windowName;
			GLFWwindow* window;
	};
}// namespace dVRE
