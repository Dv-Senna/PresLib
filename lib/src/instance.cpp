#include "pl/instance.hpp"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>



namespace pl {
	Instance::Instance(const pl::Instance::CreateInfos &createInfos) :
		m_blockFactory {{
			.heapSize = createInfos.blockHeapSize
		}},
		m_window {nullptr}
	{
		std::cout << "Create Instance of PresLib" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Can't init SDL2 : " + std::string(SDL_GetError()));

		pl::Window::CreateInfos windowCreateInfos {};
		windowCreateInfos.title = createInfos.presentationName;
		windowCreateInfos.size = createInfos.viewportSize;
		m_window = new pl::Window(windowCreateInfos);
	}


	Instance::~Instance() {
		std::cout << "Destroy Instance of PresLib" << std::endl;
		if (m_window != nullptr)
			delete m_window;
		SDL_Quit();
	}


} // namespace pl
