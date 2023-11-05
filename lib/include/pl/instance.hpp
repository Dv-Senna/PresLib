#pragma once

#include <functional>
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "config.hpp"
#include "graphics/api.inl"
#include "graphics/projection.hpp"
#include "renderer.hpp"
#include "slide.hpp"


namespace pl
{
	class Instance final
	{
		public:
			struct CreateInfo
			{
				std::string presentationTitle {pl::config::defaultPresentationTitle};
				pl::graphics::Api graphicsApi {pl::config::defaultGraphicsApi};
				glm::vec2 viewportSize {pl::config::defaultViewportSize};
				pl::graphics::Projection projection {pl::config::defaultProjection};
			};

			Instance(const pl::Instance::CreateInfo &createInfo);
			~Instance();

			pl::Renderer &getRenderer();
			void setRenderingCallback(const std::function<void()> &callback);
			std::shared_ptr<pl::Slide> registerSlide(const pl::Slide::CreateInfo &createInfos = {});
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Slide> slide, const pl::Block::CreateInfo &createInfos);
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Slide> slide, std::shared_ptr<pl::Block> block);
			const glm::mat4 &getTransformation() const noexcept;
			void setProjection(pl::graphics::Projection projection);

			void run();


		private:
			static glm::mat4 s_generateTransformationFromProjection(pl::graphics::Projection projection, const glm::vec2 &viewportSize);

			SDL_Window *m_window;
			std::unique_ptr<pl::Renderer> m_renderer;
			std::function<void()> m_renderingCallback;
			pl::utils::Id m_vertices, m_framebuffer, m_shaders[3], m_pipeline;
			std::list<std::shared_ptr<pl::Slide>> m_slides;
			std::list<std::shared_ptr<pl::Slide>>::iterator m_currentSlide;
			glm::mat4 m_transformation;
			glm::vec2 m_viewportSize;
			pl::graphics::Projection m_projection;
	};

} // namespace pl
