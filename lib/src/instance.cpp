#include "pl/instance.hpp"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>



namespace pl {
	Instance::Instance(const pl::Instance::CreateInfos &createInfos) :
		m_blockFactory {{
			.heapSize = createInfos.blockHeapSize
		}}
	{
		std::cout << "Create Instance of PresLib" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Can't init SDL2 : " + std::string(SDL_GetError()));
	}


	Instance::~Instance() {
		std::cout << "Destroy Instance of PresLib" << std::endl;
		SDL_Quit();
	}


} // namespace pl
