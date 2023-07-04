#include <iostream>

#include <SDL2/SDL_gpu.h>

#include "block.hpp"
#include "impl/SDL2_gpu/instance.hpp"



namespace pl::impl::SDL2_gpu
{
	Instance::Instance() : impl::Instance()
	{
		m_window = GPU_Init(m_windowInfos.width, m_windowInfos.height, GPU_DEFAULT_INIT_FLAGS);
		if (std::any_cast<GPU_Target*> (m_window) == nullptr)
			throw std::runtime_error("PL : Can't create an SDL_gpu target : " + std::string(SDL_GetError()));
	}



	Instance::~Instance()
	{
		GPU_Quit();
		impl::Instance::~Instance();
	}



	void Instance::run()
	{
		while (true)
		{
			if (!this->m_handleEvent())
				return;


			GPU_ClearRGB(std::any_cast<GPU_Target*> (m_window), 0, 0, 0);
			
			this->m_render();

			GPU_Flip(std::any_cast<GPU_Target*> (m_window));
		}
	}



} // namespace pl::impl::SDL2_gpu
