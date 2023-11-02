#include <iostream>
#include <map>
#include <stdexcept>

#include "graphics/framebuffer.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/shader.hpp"
#include "graphics/vertices.hpp"
#include "instance.hpp"



namespace pl
{
	Instance::Instance(const pl::Instance::CreateInfo &createInfo) : 
		m_window {nullptr},
		m_renderer {nullptr},
		m_renderingCallback {nullptr},
		m_vertices {0},
		m_framebuffer {0},
		m_shaders {0, 0},
		m_pipeline {0}
	{
		static const std::map<pl::graphics::Api, SDL_WindowFlags> flags {
			{pl::graphics::Api::OpenGL, SDL_WINDOW_OPENGL}
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



		int windowWidth {}, windowHeight {};
		SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

		float viewportRatio {createInfo.viewportSize.x / createInfo.viewportSize.y};
		float windowRatio {(float)windowWidth / (float)windowHeight};
		float scaleFactor {(createInfo.viewportSize.y * (float)windowWidth) / ((float)windowHeight * createInfo.viewportSize.x)};
		glm::vec2 viewportScaledCentered {1.f, scaleFactor};

		if (viewportRatio < windowRatio)
			viewportScaledCentered = {1.f / scaleFactor, 1.f};

		/************* setup framebuffer-related stuff *************/

		pl::graphics::Vertices verticesInfos {
			{
				viewportScaledCentered.x, viewportScaledCentered.y,    1.f, 1.f,
				-viewportScaledCentered.x, -viewportScaledCentered.y,  0.f, 0.f,
				viewportScaledCentered.x, -viewportScaledCentered.y,   1.f, 0.f,

				-viewportScaledCentered.x, viewportScaledCentered.y,   0.f, 1.f,
				-viewportScaledCentered.x, -viewportScaledCentered.y,  0.f, 0.f,
				viewportScaledCentered.x, viewportScaledCentered.y,    1.f, 1.f
			},
			{{
				{pl::graphics::VerticesChannel::color, {0, 2, 0}},
				{pl::graphics::VerticesChannel::textureCoord0, {1, 2, 2}}
			}}
		};
		m_vertices = m_renderer->registerObject(pl::utils::ObjectType::vertices, verticesInfos);


		pl::graphics::Shader vertexShaderInfos {
			pl::graphics::ShaderType::vertex,
			"shaders/framebuffer.vert.spv",
			"main"
		};
		pl::graphics::Shader fragmentShaderInfos {
			pl::graphics::ShaderType::fragment,
			"shaders/framebuffer.frag.spv",
			"main"
		};
		pl::graphics::Shader fragmentShaderMSAAInfos {
			pl::graphics::ShaderType::fragment,
			"shaders/framebufferMSAA.frag.spv",
			"main"
		};
		m_shaders[0] = m_renderer->registerObject(pl::utils::ObjectType::shader, vertexShaderInfos);
		m_shaders[1] = m_renderer->registerObject(pl::utils::ObjectType::shader, fragmentShaderInfos);
		m_shaders[2] = m_renderer->registerObject(pl::utils::ObjectType::shader, fragmentShaderMSAAInfos);

		pl::graphics::Uniform uniformInfos {
			{
				{pl::graphics::UniformFieldType::floating, "uni_SamplesCount"},
				{pl::graphics::UniformFieldType::vec2, "uni_ViewportSize"}
			},
			"uni_WindowFramebufferBlock",
			0
		};

		pl::graphics::Pipeline pipelineInfos {
			{m_shaders[0], pl::config::useMSAA ? m_shaders[2] : m_shaders[1]},
			pl::config::useMSAA ? std::vector<pl::graphics::Uniform> ({uniformInfos}) : std::vector<pl::graphics::Uniform> ()
		};
		m_pipeline = m_renderer->registerObject(pl::utils::ObjectType::pipeline, pipelineInfos);

		if (pl::config::useMSAA)
		{
			m_renderer->setUniformValues(m_pipeline, "uni_WindowFramebufferBlock", {
				{"uni_SamplesCount", static_cast<float> (pl::config::MSAASamplesCount)},
				{"uni_ViewportSize", createInfo.viewportSize}
			});
		}

		pl::graphics::Framebuffer framebufferInfos {
			createInfo.viewportSize,
			pl::config::useMSAA ? pl::config::MSAASamplesCount : 0
		};
		m_framebuffer = m_renderer->registerObject(pl::utils::ObjectType::framebuffer, framebufferInfos);

		
		/************* setup framebuffer-related stuff *************/
	}



	Instance::~Instance()
	{
		if (m_renderer.get() != nullptr)
			m_renderer.reset();

		if (m_window != nullptr)
			SDL_DestroyWindow(m_window);
	}



	pl::Renderer &Instance::getRenderer()
	{
		return *m_renderer;
	}



	void Instance::setRenderingCallback(const std::function<void()> &callback)
	{
		m_renderingCallback = callback;
	}



	void Instance::run()
	{
		SDL_Event event {};
		pl::utils::Id framebufferTexture {m_renderer->getFramebufferTexture(m_framebuffer)};

		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_KEY_DOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return;

				if (event.type == SDL_EVENT_QUIT)
					return;
			}


			m_renderer->useFramebuffer(m_framebuffer);
				m_renderer->cleanViewport({100, 100, 100, 255});

				if (m_renderingCallback != nullptr)
					m_renderingCallback();

			m_renderer->useFramebuffer(0);


			m_renderer->cleanViewport(pl::utils::black);

			m_renderer->usePipeline(m_pipeline);
				m_renderer->bindTexture(m_pipeline, framebufferTexture, 0);
					m_renderer->drawVertices(m_vertices);
				m_renderer->bindTexture(m_pipeline, 0, 0);
			m_renderer->usePipeline(0);

			m_renderer->updateScreen();
		}
	}



} // namespace pl
