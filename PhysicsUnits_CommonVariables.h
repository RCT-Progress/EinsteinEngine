#pragma once


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//std lib
#include <vector>
#include <array>

namespace EEPhysics {
	class PhysicsUnits {
	public:
		float liter;
		float gram;
		float meter;
		float joules;
		float volts;
		float watts;
		float ohms;
		float amps;
		float seconds;
		float CoM[3];
	};
}