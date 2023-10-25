#include <map>
#include <stdexcept>

#include "instance.hpp"



namespace pl
{
	Instance::Instance(const pl::Instance::CreateInfo &createInfo) : 
		m_window {nullptr}
	{
		static const std::map<pl::GraphicsApi, SDL_WindowFlags> flags {
			{pl::GraphicsApi::OpenGL, SDL_WINDOW_OPENGL}
		};

		auto it {flags.find(createInfo.graphicsApi)};
		if (it == flags.end())
			throw std::runtime_error("PL : Can't use graphics api " + std::to_string((int)createInfo.graphicsApi) + " in window");
		
		m_window = SDL_CreateWindow(
			createInfo.presentationTitle.c_str(),
			createInfo.viewportSize.x, createInfo.viewportSize.y,
			SDL_WINDOW_FULLSCREEN | it->second
		);
		if (m_window == nullptr)
			throw std::runtime_error("PL : Can't create an SDL3 window : " + std::string(SDL_GetError()));

		pl::Renderer::CreateInfo rendererCreateInfo {};
		rendererCreateInfo.graphicsApi = createInfo.graphicsApi;
		rendererCreateInfo.viewportSize = createInfo.viewportSize;
		rendererCreateInfo.window = m_window;
		m_renderer = std::make_unique<pl::Renderer> (rendererCreateInfo);
	}



	Instance::~Instance()
	{
		if (m_renderer.get() != nullptr)
			m_renderer.reset();

		if (m_window != nullptr)
			SDL_DestroyWindow(m_window);
	}



	void Instance::run()
	{
		SDL_Event event {};

		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_KEY_DOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return;

				if (event.type == SDL_EVENT_QUIT)
					return;
			}


			m_renderer->cleanViewport({100, 100, 100, 255});

			
			m_renderer->updateScreen();
		}
	}



} // namespace pl
