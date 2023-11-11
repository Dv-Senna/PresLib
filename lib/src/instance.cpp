#include <iostream>
#include <map>
#include <stdexcept>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "blocks/ellipse.hpp"
#include "blocks/group.hpp"
#include "blocks/image.hpp"
#include "blocks/math.hpp"
#include "blocks/rectangle.hpp"
#include "blocks/text.hpp"
#include "blocks/triangle.hpp"
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
		m_eventManager {},
		m_fontManager {*this},
		m_theme {nullptr},
		m_defaultStyle {},
		m_renderingCallback {nullptr},
		m_vertices {0},
		m_framebuffer {0},
		m_shaders {0, 0},
		m_pipeline {0},
		m_slides {},
		m_currentSlide {m_slides.end()},
		m_transformation {1.f},
		m_viewportSize {createInfo.viewportSize}
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
		rendererCreateInfo.viewportSize = m_viewportSize;
		rendererCreateInfo.window = m_window;
		m_renderer = std::make_unique<pl::Renderer> (rendererCreateInfo);



		int windowWidth {}, windowHeight {};
		SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

		float viewportRatio {m_viewportSize.x / m_viewportSize.y};
		float windowRatio {(float)windowWidth / (float)windowHeight};
		float scaleFactor {(m_viewportSize.y * (float)windowWidth) / ((float)windowHeight * m_viewportSize.x)};
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
				{"uni_ViewportSize", m_viewportSize}
			});
		}

		pl::graphics::Framebuffer framebufferInfos {
			m_viewportSize,
			pl::config::useMSAA ? pl::config::MSAASamplesCount : 0
		};
		m_framebuffer = m_renderer->registerObject(pl::utils::ObjectType::framebuffer, framebufferInfos);

		
		/************* setup framebuffer-related stuff *************/


		//m_transformation = glm::ortho(0.f, m_viewportSize.x, 0.f, m_viewportSize.y);
		m_transformation = glm::ortho(0.f, (float)windowWidth, 0.f, (float)windowHeight);
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
		pl::utils::Id framebufferTexture {m_renderer->getFramebufferTexture(m_framebuffer)};
		pl::graphics::RenderMode renderMode {pl::graphics::RenderMode::normal};
		auto startTime {std::chrono::steady_clock::now()};
		float dt {1.f};
		
		float dtSum {0.f};
		int dtCount {0};
		bool monitoring {false};

		while (m_eventManager.pollEvent())
		{
			if (monitoring)
			{
				++dtCount;
				dtSum += dt;
			}



			if (m_eventManager.isKeyDown(SDL_SCANCODE_ESCAPE))
				return;

			if (m_eventManager.isKeyPressed(SDL_SCANCODE_LEFT))
			{
				if (!m_slides.empty() && m_currentSlide != m_slides.begin())
					--m_currentSlide;
			}

			if (m_eventManager.isKeyPressed(SDL_SCANCODE_RIGHT) || m_eventManager.isKeyPressed(SDL_SCANCODE_SPACE))
			{
				if (!m_slides.empty())
					++m_currentSlide;
				if (m_currentSlide == m_slides.end())
					return;
			}

			if (m_eventManager.isKeyPressed(SDL_SCANCODE_E))
			{
				if (renderMode == pl::graphics::RenderMode::normal)
					renderMode = pl::graphics::RenderMode::wireframe;
				
				else
					renderMode = pl::graphics::RenderMode::normal;

				m_renderer->setRenderMode(renderMode);
			}

			if (m_eventManager.isKeyPressed(SDL_SCANCODE_P))
			{
				if (monitoring)
				{
					std::cout << "Average performance on " << dtCount << " frames : dt=" << dtSum / (float)dtCount
					<< " | fps=" << 1000.f * (float)dtCount / dtSum << std::endl;
					dtCount = 0;
					dtSum = 0.f;
				}

				else
				{
					dtCount = 1;
					dtSum = dt;
				}

				monitoring = !monitoring;
			}

			pl::utils::Color clearColor {m_defaultStyle.colors.background};
			if (m_theme != nullptr)
				clearColor = m_theme->getStyle().colors.background;

			m_renderer->useFramebuffer(m_framebuffer);
				m_renderer->cleanViewport(clearColor);

				if (m_theme != nullptr)
					m_theme->preRendering();

				if (m_currentSlide != m_slides.end())
					(*m_currentSlide)->draw(m_transformation);

				if (m_theme != nullptr)
					m_theme->postRendering();

				if (m_renderingCallback != nullptr)
					m_renderingCallback();

			m_renderer->useFramebuffer(0);


			m_renderer->cleanViewport(pl::utils::black);

			m_renderer->usePipeline(m_pipeline);
				m_renderer->bindTexture(m_pipeline, framebufferTexture, 0);
					m_renderer->drawVertices(m_vertices, true);
				m_renderer->bindTexture(m_pipeline, 0, 0);
			m_renderer->usePipeline(0);

			m_renderer->updateScreen();

			dt = std::chrono::duration_cast<std::chrono::duration<float, std::milli>> (
				std::chrono::steady_clock::now() - startTime).count();
			startTime = std::chrono::steady_clock::now();
		}
	}



	std::shared_ptr<pl::Slide> Instance::registerSlide(const pl::Slide::CreateInfo &createInfos)
	{
		m_slides.push_back(std::shared_ptr<pl::Slide> (new pl::Slide(createInfos)));
		if (m_slides.size() == 1)
			m_currentSlide = m_slides.begin();

		if (m_theme != nullptr)
			m_theme->registerSlide(*m_slides.rbegin(), createInfos);

		return *m_slides.rbegin();
	}



	std::shared_ptr<pl::Block> Instance::registerBlock(std::shared_ptr<pl::Slide> slide, const pl::Block::CreateInfo &createInfos)
	{
		if (slide.get() == nullptr)
			throw std::runtime_error("PL : Can't register new block because slide is invalid");

		auto block {pl::Instance::s_createBlock(*this, createInfos)};
		if (block.get() == nullptr)
			throw std::runtime_error("PL : Newly created block is null");

		slide->registerBlock(block);
		return block;
	}



	std::shared_ptr<pl::Block> Instance::registerBlock(std::shared_ptr<pl::Slide> slide, std::shared_ptr<pl::Block> block)
	{
		if (slide.get() == nullptr)
			throw std::runtime_error("PL : Can't register block because slide is invalid");

		if (block.get() == nullptr)
			throw std::runtime_error("PL : Can't register block because the given block is not valid");

		slide->registerBlock(block);
		return block;
	}



	std::shared_ptr<pl::Block> Instance::registerBlock(std::shared_ptr<pl::Block> group, const pl::Block::CreateInfo &createInfos)
	{
		if (group.get() == nullptr)
			throw std::runtime_error("PL : Can't register new block because group is invalid");

		auto block {pl::Instance::s_createBlock(*this, createInfos)};
		if (block.get() == nullptr)
			throw std::runtime_error("PL : Newly created block is null");

		group.get()->registerBlock(block);
		return block;
	}



	std::shared_ptr<pl::Block> Instance::registerBlock(std::shared_ptr<pl::Block> group, std::shared_ptr<pl::Block> block)
	{
		if (group.get() == nullptr)
			throw std::runtime_error("PL : Can't register block because group is invalid");

		if (block.get() == nullptr)
			throw std::runtime_error("PL : Can't register block because the given block is not valid");

		group->registerBlock(block);
		return block;
	}



	const glm::mat4 &Instance::getTransformation() const noexcept
	{
		return m_transformation;
	}



	const pl::EventManager &Instance::getEvent() const noexcept
	{
		return m_eventManager;
	}



	pl::FontManager &Instance::getFont() noexcept
	{
		return m_fontManager;
	}



	void Instance::useTheme(pl::Theme *theme)
	{
		m_theme = theme;
	}



	const pl::Style &Instance::getStyle() const noexcept
	{
		if (m_theme != nullptr)
			return m_theme->getStyle();

		return m_defaultStyle;
	}



	std::shared_ptr<pl::Block> Instance::s_createBlock(pl::Instance &instance, const pl::Block::CreateInfo &createInfos)
	{
		switch (createInfos.type)
		{
			case pl::Block::Type::rectangle:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Rectangle::CreateInfo))
					throw std::runtime_error("PL : Can't register rectangle block because given data are invalid");

				return std::make_shared<pl::blocks::Rectangle> (
					instance, std::any_cast<pl::blocks::Rectangle::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::triangle:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Triangle::CreateInfo))
					throw std::runtime_error("PL : Can't register triangle block because given data are invalid");

				return std::make_shared<pl::blocks::Triangle> (
					instance, std::any_cast<pl::blocks::Triangle::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::group:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Group::CreateInfo))
					throw std::runtime_error("PL : Can't register group block because given data are invalid");

				return std::make_shared<pl::blocks::Group> (
					instance, std::any_cast<pl::blocks::Group::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::line:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Line::CreateInfo))
					throw std::runtime_error("PL : Can't register line block because given data are invalid");

				return std::make_shared<pl::blocks::Line> (
					instance, std::any_cast<pl::blocks::Line::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::ellipse:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Ellipse::CreateInfo))
					throw std::runtime_error("PL : Can't register ellipse block because given data are invalid");

				return std::make_shared<pl::blocks::Ellipse> (
					instance, std::any_cast<pl::blocks::Ellipse::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::math:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Math::CreateInfo))
					throw std::runtime_error("PL : Can't register math block because given data are invalid");

				return std::make_shared<pl::blocks::Math> (
					instance, std::any_cast<pl::blocks::Math::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::image:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Image::CreateInfo))
					throw std::runtime_error("PL : Can't register image block because given data are invalid");

				return std::make_shared<pl::blocks::Image> (
					instance, std::any_cast<pl::blocks::Image::CreateInfo> (createInfos.data)
				);
				break;

			case pl::Block::Type::text:
				if (!createInfos.data.has_value() || createInfos.data.type() != typeid(pl::blocks::Text::CreateInfo))
					throw std::runtime_error("PL : Can't register text block because given data are invalid");

				return std::make_shared<pl::blocks::Text> (
					instance, std::any_cast<pl::blocks::Text::CreateInfo> (createInfos.data)
				);
				break;

			default:
				throw std::runtime_error("PL : Can't register new block because type is not valid");
		}

		return std::shared_ptr<pl::Block> (nullptr);
	}



} // namespace pl
