#include "pl/window.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include <glad/glad.h>



namespace pl {
	void APIENTRY debugOutput(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char *message,
		const void *userData
	) {
		static const std::map<GLenum, std::string> sourceMap {
			{GL_DEBUG_SOURCE_API,             "API"},
			{GL_DEBUG_SOURCE_WINDOW_SYSTEM,   "Window System"},
			{GL_DEBUG_SOURCE_SHADER_COMPILER, "Shader Compiler"},
			{GL_DEBUG_SOURCE_THIRD_PARTY,     "Third Party"},
			{GL_DEBUG_SOURCE_APPLICATION,     "Application"},
			{GL_DEBUG_SOURCE_OTHER,           "Other"}
		};

		static const std::map<GLenum, std::string> typeMap {
			{GL_DEBUG_TYPE_ERROR,               "Error"},
			{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated Behaviour"},
			{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,  "Undefined Behaviour"},
			{GL_DEBUG_TYPE_PORTABILITY,         "Portability"},
			{GL_DEBUG_TYPE_PERFORMANCE,         "Performance"},
			{GL_DEBUG_TYPE_MARKER,              "Marker"},
			{GL_DEBUG_TYPE_PUSH_GROUP,          "Push Group"},
			{GL_DEBUG_TYPE_POP_GROUP,           "Pop Group"},
			{GL_DEBUG_TYPE_OTHER,               "Other"}
		};
		
		static const std::map<GLenum, std::string> severityMap {
			{GL_DEBUG_SEVERITY_HIGH,         "high"},
			{GL_DEBUG_SEVERITY_MEDIUM,       "medium"},
			{GL_DEBUG_SEVERITY_LOW,          "low"},
			{GL_DEBUG_SEVERITY_NOTIFICATION, "notification"}
		};

		std::cout << "OpenGL Debug (" << sourceMap.find(source)->second << ") " << typeMap.find(type)->second
			<< " : " << severityMap.find(severity)->second << " > " << message << std::endl;
	}

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);


		m_context = SDL_GL_CreateContext(m_window);
		if (m_context == nullptr)
			throw std::runtime_error("Can't create an SDL2 OpenGL 4.6 context : " + std::string(SDL_GetError()));

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
			throw std::runtime_error("Can't load OpenGL function with GLAD");

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		glFrontFace(GL_CCW);
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
		pl::Uint32 flag {fullscreen ? (pl::Uint32)SDL_WINDOW_FULLSCREEN_DESKTOP : 0};
		SDL_SetWindowFullscreen(m_window, flag);
	}


	void Window::swap() {
		SDL_GL_SwapWindow(m_window);
	}


} // namespace pl
