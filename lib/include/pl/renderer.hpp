#pragma once

#include <memory>

#include <SDL3/SDL.h>

#include "graphicsApi.inl"
#include "math/vec2.hpp"
#include "utils/color.hpp"


namespace pl
{	
	class Renderer
	{
		public:
			struct CreateInfo
			{
				pl::math::Vec2i viewportSize;
				SDL_Window *window;
				pl::GraphicsApi graphicsApi;
			};

			struct Implementation;
			struct Functions
			{
				void (*setup) (pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &createInfo) {nullptr};
				void (*cleanup) (pl::Renderer::Implementation *impl) {nullptr};
				void (*cleanViewport) (pl::Renderer::Implementation *impl, const pl::utils::Color &color) {nullptr};
				void (*updateScreen) (pl::Renderer::Implementation *impl) {nullptr};

				inline bool isOneNotSet()
				{
					return !(setup && cleanup && cleanViewport && updateScreen);
				}
			};

			struct Implementation
			{
				std::shared_ptr<void> internalState {nullptr};
				pl::math::Vec2i viewportSize;
				SDL_Window *window;
				pl::Renderer::Functions functions {};
			};


			Renderer(const pl::Renderer::CreateInfo &createInfo);
			~Renderer();

			void cleanViewport(const pl::utils::Color &color);
			void updateScreen();

		
		private:
			pl::Renderer::Implementation m_impl;
	};

} // namespace pl
