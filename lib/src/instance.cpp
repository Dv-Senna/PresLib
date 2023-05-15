#include <stdexcept>

#include <SDL2/SDL.h>

#include "instance.hpp"



namespace pl
{
	Instance::Instance() : m_window {nullptr}, m_renderer {nullptr}
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("PL : Can't init SDL2 : " + std::string(SDL_GetError()));

		m_window = SDL_CreateWindow(
			"Presentation",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			PL_DEFAULT_VIEWPORT_WIDTH,
			PL_DEFAULT_VIEWPORT_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (m_window == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 window : " + std::string(SDL_GetError()));

		if (SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
			throw std::runtime_error("PL : Can't set window to fullscreen : " + std::string(SDL_GetError()));


		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (m_renderer == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 renderer : " + std::string(SDL_GetError()));

		
		if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_ADD) != 0)
			throw std::runtime_error("PL : Can't change renderer blend mode : " + std::string(SDL_GetError()));
	}



	Instance::~Instance()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}



	void Instance::run()
	{
		bool running {true};
		SDL_Event event {};

		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_KEYDOWN:
						if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
							running = false;
						break;

					case SDL_QUIT:
						running = false;
						break;
				}
			}
		}


		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);


		SDL_RenderPresent(m_renderer);
	}



} // namespace pl
