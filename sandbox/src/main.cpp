#include <iostream>
#include <exception>

#include <pl/preslib.hpp>

#include <pl/memory/heapAllocator.hpp>



int main(int, char *[]) {
	try {
		pl::Instance::CreateInfos instanceCreateInfos {};
		instanceCreateInfos.blockHeapSize = 1024*1024;
		pl::Instance instance {instanceCreateInfos};
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
