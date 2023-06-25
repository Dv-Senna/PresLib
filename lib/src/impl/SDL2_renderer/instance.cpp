#include "block.hpp"
#include "impl/SDL2_renderer/instance.hpp"



namespace pl::impl::SDL2_renderer
{
	Instance::Instance() : impl::Instance(), m_handler {nullptr}
	{
		this->m_createWindow();

		m_handler = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (m_handler == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 renderer : " + std::string(SDL_GetError()));
	}



	Instance::~Instance()
	{
		SDL_DestroyRenderer(m_handler);
		impl::Instance::~Instance();
	}



	void Instance::run()
	{
		SDL_Event event {};

		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					return;
			}


			SDL_SetRenderDrawColor(m_handler, 0, 0, 0, 255);
			SDL_RenderClear(m_handler);

			SDL_SetRenderDrawColor(m_handler, 255, 255, 255, 255);
			for (auto child : m_children)
				child->render();

			SDL_RenderPresent(m_handler);
		}
	}



} // namespace pl::impl::SDL2_renderer
