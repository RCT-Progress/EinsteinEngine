
#include "dVRE_main.h"

//std lib
#include <cstdlib>
#include <iostream>
#include <stdexcept>


int main() {
	dVRE::MainApp app{};

	try {
		app.run();
	}catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}