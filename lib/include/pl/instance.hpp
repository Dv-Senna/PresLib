#pragma once

#include <functional>
#include <memory>
#include <string>

#include <SDL3/SDL.h>

#include "config.hpp"
#include "graphics/api.inl"
#include "math/vec2.hpp"
#include "renderer.hpp"


namespace pl
{
	class Instance final
	{
		public:
			struct CreateInfo
			{
				std::string presentationTitle {pl::config::defaultPresentationTitle};
				pl::graphics::Api graphicsApi {pl::config::defaultGraphicsApi};
				pl::math::Vec2i viewportSize {pl::config::defaultViewportSize};
			};

			Instance(const pl::Instance::CreateInfo &createInfo);
			~Instance();

			pl::Renderer &getRenderer();
			void setRenderingCallback(const std::function<void()> &callback);

			void run();


		private:
			SDL_Window *m_window;
			std::unique_ptr<pl::Renderer> m_renderer;
			std::function<void()> m_renderingCallback;
	};

} // namespace pl
