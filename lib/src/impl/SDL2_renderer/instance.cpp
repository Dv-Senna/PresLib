#include "block.hpp"
#include "impl/SDL2_renderer/instance.hpp"



namespace pl::impl::SDL2_renderer
{
	Instance::Instance() : impl::Instance(), m_handler {nullptr}
	{
		this->m_initSDL2();

		m_handler = SDL_CreateRenderer(std::any_cast<SDL_Window*> (m_window), -1, SDL_RENDERER_ACCELERATED);
		if (m_handler == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 renderer : " + std::string(SDL_GetError()));
	}



	Instance::~Instance()
	{
		SDL_DestroyRenderer(m_handler);
		this->m_quitSDL2();
		impl::Instance::~Instance();
	}



	void Instance::run()
	{
		while (true)
		{
			if (!this->m_handleEvent())
				return;


			SDL_SetRenderDrawColor(m_handler, 0, 0, 0, 255);
			SDL_RenderClear(m_handler);
			
			this->m_render();

			SDL_RenderPresent(m_handler);
		}
	}



} // namespace pl::impl::SDL2_renderer
