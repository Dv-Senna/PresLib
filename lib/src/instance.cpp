#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "block.hpp"
#include "instance.hpp"
#include "slide.hpp"
#include "utils/framerate.hpp"



namespace pl
{
	Instance::Instance() : 
		m_window {nullptr},
		m_openglContext {nullptr},
		m_fontManager {nullptr},
		m_colorManager {},
		m_shaderManager {nullptr},
		m_slides {},
		m_currentSlide {0},
		m_background {nullptr},
		m_overlay {nullptr},
		m_titlePosition {},
		m_titleFontSize {},
		m_renderingCallback {nullptr}
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("PL : Can't init SDL2 : " + std::string(SDL_GetError()));

		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
			throw std::runtime_error("PL : Can't init SDL2_image : " + std::string(IMG_GetError()));

		if (TTF_Init() != 0)
			throw std::runtime_error("PL : Can't init SDL2_ttf : " + std::string(TTF_GetError()));



		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) != 0)
			throw std::runtime_error("PL : Can't set SDL OpenGL context attribute 'major version' : " + std::string(SDL_GetError()));
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) != 0)
			throw std::runtime_error("PL : Can't set SDL OpenGL context attribute 'minor version' : " + std::string(SDL_GetError()));
		if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) != 0)
			throw std::runtime_error("PL : Can't set SDL OpenGL context attribute 'depth size' : " + std::string(SDL_GetError()));
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0)
			throw std::runtime_error("PL : Can't set SDL OpenGL context attribute 'double buffer' : " + std::string(SDL_GetError()));


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

		m_openglContext = SDL_GL_CreateContext(m_window);
		if (m_openglContext == nullptr)
			throw std::runtime_error("PL : Can't create an SDL OpenGL context : " + std::string(SDL_GetError()));


		GLenum glewRet {glewInit()};
		if (glewRet != GLEW_OK)
			throw std::runtime_error("PL : Can't init GLEW : " + std::string((const char*)glewGetErrorString(glewRet)));

		
		m_fontManager = new pl::FontManager();
		m_shaderManager = new pl::ShaderManager();
	}



	Instance::~Instance()
	{
		delete m_shaderManager;
		delete m_fontManager;

		SDL_GL_DeleteContext(m_openglContext);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}



	void Instance::run()
	{
		bool running {true};
		SDL_Event event {};

		//SDL_Rect background {0, 0, PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT};

		pl::utils::FPSManager fpsManager {60};


		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_KEYDOWN:
						if (
							event.key.keysym.scancode == SDL_SCANCODE_SPACE ||
							event.key.keysym.scancode == SDL_SCANCODE_RIGHT
						)
						{
							m_currentSlide++;
							if (m_currentSlide == m_slides.size())
								running = false;
						}

						else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
						{
							if (m_currentSlide != 0)
								m_currentSlide--;
						}

						else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
							running = false;
						break;

					case SDL_QUIT:
						running = false;
						break;
				}
			}


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			if (m_currentSlide != m_slides.size())
			{
				if (m_background != nullptr && !(m_slides[m_currentSlide]->getFlags() & pl::SlideFlag::no_background))
					m_background->render();


				m_slides[m_currentSlide]->render();


				if (m_overlay != nullptr && !(m_slides[m_currentSlide]->getFlags() & pl::SlideFlag::no_overlay))
					m_overlay->render();
			}

			if (m_renderingCallback != nullptr)
				m_renderingCallback(this);


			SDL_GL_SwapWindow(m_window);

			fpsManager.cap();
		}
	}
	


	void Instance::addSlide(pl::Slide *slide)
	{
		m_slides.push_back(slide);
	}



	void Instance::setCustomRenderingCallback(pl::Instance::RenderingCallback renderingCallback)
	{
		m_renderingCallback = renderingCallback;
	}



	void Instance::setSharedBackground(pl::Block *background)
	{
		m_background = background;
	}



	void Instance::setSharedOverlay(pl::Block *overlay)
	{
		m_overlay = overlay;
	}



	void Instance::setTitlePosition(const pl::math::Vec2 &position)
	{
		m_titlePosition = position;
	}



	void Instance::setTitleFontSize(int fontSize)
	{
		m_titleFontSize = fontSize;
	}



} // namespace pl
