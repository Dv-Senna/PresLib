#include <iostream>

#include "block.hpp"
#include "impl/SDL2_renderer/instance.hpp"



namespace pl::impl::SDL2_renderer
{
	Instance::Instance() : impl::Instance(), m_handler {nullptr}
	{
		this->m_initSDL2();

		m_handler = SDL_CreateRenderer(std::any_cast<SDL_Window*> (m_window), -1, SDL_RENDERER_ACCELERATED);
		if (m_handler == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2_Renderer* : " + std::string(SDL_GetError()));

		if (SDL_RenderSetLogicalSize(m_handler, PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT) != 0)
			throw std::runtime_error("PL : Can't set viewport size : " + std::string(SDL_GetError()));

		if (SDL_SetRenderDrawBlendMode(m_handler, SDL_BLENDMODE_BLEND) != 0)
			throw std::runtime_error("PL : Can't change SDL2_Renderer* blend mode : " + std::string(SDL_GetError()));

		bool result {SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best")};

		#ifndef NDEBUG

			if (!result)
				std::cout << "Antialiasing was not enabled" << std::endl;

		#endif
	}



	Instance::~Instance()
	{
		SDL_DestroyRenderer(m_handler);
		this->m_quitSDL2();
	}



	void Instance::run()
	{
		SDL_FRect backgroundRect {0.0f, 0.0f, PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT};

		while (true)
		{
			if (!this->m_handleEvent())
				return;


			SDL_SetRenderDrawColor(m_handler, 0, 0, 0, 255);
			SDL_RenderClear(m_handler);

			SDL_SetRenderDrawColor(
				m_handler,
				m_theme->style.backgroundColor.r,
				m_theme->style.backgroundColor.g,
				m_theme->style.backgroundColor.b,
				255
			);
			SDL_RenderFillRectF(m_handler, &backgroundRect);

			this->m_render();

			SDL_RenderPresent(m_handler);
		}
	}



} // namespace pl::impl::SDL2_renderer
