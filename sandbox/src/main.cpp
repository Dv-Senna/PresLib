#include <iostream>
#include <exception>

#include <pl/preslib.hpp>



int main(int, char *[]) {
	try {
		pl::InstanceCreateInfos instanceCreateInfos {};
		pl::Instance instance {instanceCreateInfos};
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
