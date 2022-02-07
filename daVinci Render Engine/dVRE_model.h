#pragma once

#include "dVRE_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//std lib
#include <vector>

namespace dVRE {
	class dVREmodel { 
	public:
		struct Vertex {
			glm::vec2 position;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};
		dVREmodel(dVREdevice& device, const std::vector<Vertex> &vertices);
		~dVREmodel();

		dVREmodel(const dVREmodel&) = delete;
		dVREmodel &operator=(const dVREmodel&) = delete;

		void bind(VkCommandBuffer commandbuffer);
		void draw(VkCommandBuffer commandbuffer);


	private:
		void createVertexBuffers(const std::vector<Vertex> &vertices);

		dVREdevice& dvreDevice;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
	};
}