#pragma once

#include <any>
#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "graphics/api.inl"
#include "graphics/efficiency.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/renderMode.hpp"
#include "graphics/uniform.hpp"
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
				glm::vec2 viewportSize;
				SDL_Window *window;
				pl::graphics::Api graphicsApi;
				std::string windowTitle;
				pl::graphics::Efficency efficency;
			};

			struct Implementation;
			struct Functions
			{
				void (*setup) (pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &createInfo) {nullptr};
				void (*cleanup) (pl::Renderer::Implementation *impl) {nullptr};
				void (*cleanViewport) (
					pl::Renderer::Implementation *impl, const pl::utils::Color &color, pl::graphics::CleanFlag flag) {nullptr};
				void (*updateScreen) (pl::Renderer::Implementation *impl) {nullptr};
				pl::utils::Id (*registerObject) (
					pl::Renderer::Implementation *impl,
					pl::utils::ObjectType type,
					const std::any &data
				) {nullptr};
				pl::utils::ObjectType (*getObjectType) (pl::Renderer::Implementation *impl, pl::utils::Id objectID) {nullptr};
				void (*usePipeline) (pl::Renderer::Implementation *impl, pl::utils::Id pipeline) {nullptr};
				void (*drawVertices) (pl::Renderer::Implementation *impl, pl::utils::Id vertices, bool forceNormalRenderMode) {nullptr};
				void (*setUniformValues) (
					pl::Renderer::Implementation *impl,
					pl::utils::Id pipeline,
					const std::string &uboName,
					const std::vector<pl::graphics::UniformFieldValue> &values
				) {nullptr};
				void (*bindTexture) (
					pl::Renderer::Implementation *impl,
					pl::utils::Id pipeline,
					pl::utils::Id texture,
					int bindingPoint
				) {nullptr};
				void (*useFramebuffer) (pl::Renderer::Implementation *impl, pl::utils::Id framebuffer) {nullptr};
				pl::utils::Id (*getFramebufferTexture) (pl::Renderer::Implementation *impl, pl::utils::Id framebuffer) {nullptr};
				void (*setRenderMode) (pl::Renderer::Implementation *impl, pl::graphics::RenderMode renderMode);

				inline bool isOneNotSet()
				{
					return !(setup && cleanup && cleanViewport && updateScreen && registerObject
						&& getObjectType && usePipeline && drawVertices && setUniformValues && bindTexture
						&& useFramebuffer && getFramebufferTexture && setRenderMode
					);
				}
			};

			struct Implementation
			{
				std::shared_ptr<void> internalState {nullptr};
				glm::vec2 viewportSize;
				SDL_Window *window;
				pl::graphics::RenderMode renderMode {pl::graphics::RenderMode::normal};
				pl::Renderer::Functions functions {};
			};


			Renderer(const pl::Renderer::CreateInfo &createInfo);
			~Renderer();

			void cleanViewport(const pl::utils::Color &color, pl::graphics::CleanFlag flag = pl::graphics::CleanFlag::color);
			void updateScreen();
			pl::utils::Id registerObject(
				pl::utils::ObjectType type, const std::any &data
			);
			pl::utils::ObjectType getObjectType(pl::utils::Id objectID);
			void usePipeline(pl::utils::Id pipeline);
			void drawVertices(pl::utils::Id vertices, bool forceNormalRenderMode = false);
			void setUniformValues(
				pl::utils::Id pipeline, const std::string &uboName, const std::vector<pl::graphics::UniformFieldValue> &values
			);
			void bindTexture(pl::utils::Id pipeline, pl::utils::Id texture, int bindingPoint);
			void useFramebuffer(pl::utils::Id framebuffer);
			pl::utils::Id getFramebufferTexture(pl::utils::Id framebuffer);
			void setRenderMode(pl::graphics::RenderMode renderMode);


		
		private:
			pl::Renderer::Implementation m_impl;
	};

} // namespace pl
