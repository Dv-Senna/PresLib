#pragma once

#include <memory>
#include <string>

#include <SDL3/SDL.h>

#include "config.hpp"
#include "graphicsApi.inl"
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
				pl::GraphicsApi graphicsApi {pl::config::defaultGraphicsApi};
				pl::math::Vec2i viewportSize {pl::config::defaultViewportSize};
			};

			Instance(const pl::Instance::CreateInfo &createInfo);
			~Instance();

			void run();


		private:
			SDL_Window *m_window;
			std::unique_ptr<pl::Renderer> m_renderer;
	};

} // namespace pl
