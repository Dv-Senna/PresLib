#include <iostream>
#include <exception>

#include <pl/preslib.hpp>



int main(int, char *[]) {
	try {
		
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}