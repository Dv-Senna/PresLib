#include <iostream>
#include <exception>

#include <pl/preslib.hpp>

#include <pl/memory/heapAllocator.hpp>



int main(int, char *[]) {
	try {
		pl::Instance::CreateInfos instanceCreateInfos {};
		instanceCreateInfos.presentationName = "Example";
		instanceCreateInfos.viewportSize = {16*70, 9*70};
		instanceCreateInfos.blockHeapSize = 1024*1024;
		pl::Instance instance {instanceCreateInfos};

		bool running {true};
		while (running) {
			SDL_Event event {};
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_WINDOWEVENT) {
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						instance.getWindow().handleResize();
						continue;
					}

					continue;
				}

				if (event.type == SDL_QUIT) {
					running = false;
					break;
				}
			}
		}
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
