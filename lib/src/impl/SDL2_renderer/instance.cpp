#include <stdexcept>

#include <SDL2/SDL.h>

#include "defines.inl"
#include "impl/SDL2_renderer/instance.hpp"



namespace pl::impl::SDL2_renderer
{
	Instance::Instance(const std::string &title, pl::impl::manager::Event *eventManager) :
		pl::impl::Instance(title, eventManager),
		m_window {static_cast<SDL_Window*> (nullptr)},
		m_renderer {static_cast<SDL_Renderer*> (nullptr)}
	{
		SDL_Window *window {nullptr};
		SDL_Renderer *renderer {nullptr};

		window = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP
		);
		if (window == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 window for 'SDL2_renderer' : " + std::string(SDL_GetError()));

		m_window = window;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 renderer for 'SDL2_renderer' : " + std::string(SDL_GetError()));

		m_renderer = renderer;
	}



	Instance::~Instance()
	{
		if (m_renderer.type() == typeid(SDL_Renderer*) && std::any_cast<SDL_Renderer*> (m_renderer) != nullptr)
			SDL_DestroyRenderer(std::any_cast<SDL_Renderer*> (m_renderer));

		if (m_window.type() == typeid(SDL_Window*) && std::any_cast<SDL_Window*> (m_window) != nullptr)
			SDL_DestroyWindow(std::any_cast<SDL_Window*> (m_window));
	}



	void Instance::run()
	{
		if (m_window.type() != typeid(SDL_Window*) || std::any_cast<SDL_Window*> (m_window) == nullptr)
			throw std::runtime_error("PL : Can't run 'SDL2_renderer' instance because window is not initialized");

		if (m_renderer.type() != typeid(SDL_Renderer*) || std::any_cast<SDL_Renderer*> (m_renderer) == nullptr)
			throw std::runtime_error("PL : Can't run 'SDL2_renderer' instance because renderer is not initialized");


		while (m_mainloop());
	}



	bool Instance::m_mainloop()
	{
		static SDL_Window *window {std::any_cast<SDL_Window*> (m_window)};
		static SDL_Renderer *renderer {std::any_cast<SDL_Renderer*> (m_renderer)};


		if (!m_eventManager->process())
			return false;


		return true;
	}



	const std::any &Instance::getHandler() const noexcept
	{
		return m_renderer;
	}



} // namespace pl::impl::SDL2_renderer
