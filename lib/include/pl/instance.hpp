#pragma once

#include <functional>
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "animationManager.hpp"
#include "config.hpp"
#include "eventManager.hpp"
#include "fontManager.hpp"
#include "graphics/api.inl"
#include "renderer.hpp"
#include "slide.hpp"
#include "theme.hpp"


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
			};

			Instance(const pl::Instance::CreateInfo &createInfo);
			~Instance();

			pl::Renderer &getRenderer();
			void setRenderingCallback(const std::function<void()> &callback);
			std::shared_ptr<pl::Slide> registerSlide(const pl::Slide::CreateInfo &createInfos = {});
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Slide> slide, const pl::Block::CreateInfo &createInfos);
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Slide> slide, std::shared_ptr<pl::Block> block);
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Block> group, const pl::Block::CreateInfo &createInfos);
			std::shared_ptr<pl::Block> registerBlock(std::shared_ptr<pl::Block> group, std::shared_ptr<pl::Block> block);
			std::shared_ptr<pl::Animation> registerAnimation(std::shared_ptr<pl::Slide> slide, const pl::Animation::CreateInfo &createInfo);
			std::shared_ptr<pl::Animation> registerAnimation(std::shared_ptr<pl::Slide> slide, std::shared_ptr<pl::Animation> animation);
			const glm::mat4 &getTransformation() const noexcept;
			const pl::EventManager &getEvent() const noexcept;
			pl::FontManager &getFont() noexcept;
			void useTheme(pl::Theme *theme);
			const pl::Style &getStyle() const noexcept;

			void run();


		private:
			static std::shared_ptr<pl::Block> s_createBlock(pl::Instance &instance, const pl::Block::CreateInfo &createInfos);

			SDL_Window *m_window;
			std::unique_ptr<pl::Renderer> m_renderer;
			pl::AnimationManager m_animationManager;
			pl::EventManager m_eventManager;
			pl::FontManager m_fontManager;
			pl::Theme *m_theme;
			pl::Style m_defaultStyle;
			std::function<void()> m_renderingCallback;
			pl::utils::Id m_vertices, m_framebuffer, m_shaders[3], m_pipeline;
			std::list<std::shared_ptr<pl::Slide>> m_slides;
			std::list<std::shared_ptr<pl::Slide>>::iterator m_currentSlide;
			glm::mat4 m_transformation;
			glm::vec2 m_viewportSize;
	};

} // namespace pl
