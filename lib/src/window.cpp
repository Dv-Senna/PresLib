#include "pl/window.hpp"

#include <stdexcept>



namespace pl {
	Window::Window(const pl::Window::CreateInfos &createInfos) :
		m_window {nullptr},
		m_context {nullptr},
		m_size {createInfos.size}
	{
		m_window = SDL_CreateWindow(
			createInfos.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_size.x, m_size.y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);
		if (m_window == nullptr)
			throw std::runtime_error("Can't create SDL2 window : " + std::string(SDL_GetError()));

		SDL_SetWindowMinimumSize(m_window, m_size.x, m_size.y);


		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


		m_context = SDL_GL_CreateContext(m_window);
		if (m_context == nullptr)
			throw std::runtime_error("Can't create an SDL2 OpenGL 4.6 context : " + std::string(SDL_GetError()));
	}


	Window::~Window() {
		if (m_context != nullptr)
			SDL_GL_DeleteContext(m_context);

		if (m_window != nullptr)
			SDL_DestroyWindow(m_window);
	}


	void Window::handleResize() {
		SDL_GetWindowSize(m_window, &m_size.x, &m_size.y);
	}


	void Window::setFullscreen(bool fullscreen) {
		pl::Uint32 flag {fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0};
		SDL_SetWindowFullscreen(m_window, flag);
	}


} // namespace pl
