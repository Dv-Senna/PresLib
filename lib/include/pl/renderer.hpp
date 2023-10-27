#pragma once

#include <any>
#include <memory>

#include <SDL3/SDL.h>

#include "graphicsApi.inl"
#include "math/vec2.hpp"
#include "utils/color.hpp"
#include "utils/id.hpp"
#include "utils/objectType.hpp"


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
				pl::utils::Id (*registerObject) (
					pl::Renderer::Implementation *impl,
					pl::utils::ObjectType type,
					const std::any &data,
					pl::utils::IdType idType
				) {nullptr};
				pl::utils::ObjectType (*getObjectType) (pl::Renderer::Implementation *impl, pl::utils::Id objectID) {nullptr};

				inline bool isOneNotSet()
				{
					return !(setup && cleanup && cleanViewport && updateScreen && registerObject && getObjectType);
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
			pl::utils::Id registerObject(
				pl::utils::ObjectType type, const std::any &data, pl::utils::IdType idType = pl::utils::IdType::external
			);
			pl::utils::ObjectType getObjectType(pl::utils::Id objectID);

		
		private:
			pl::Renderer::Implementation m_impl;
	};

} // namespace pl
