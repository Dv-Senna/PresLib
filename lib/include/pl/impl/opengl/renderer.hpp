#pragma once

#include "../../renderer.hpp"


namespace pl::impl::opengl
{
	class Renderer
	{
		public:
			static void setup(pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &createInfo);
			static void cleanup(pl::Renderer::Implementation *impl);
			static void cleanViewport(pl::Renderer::Implementation *impl, const pl::utils::Color &color, pl::graphics::CleanFlag flag);
			static void updateScreen(pl::Renderer::Implementation *impl);
			static pl::utils::Id registerObject(
				pl::Renderer::Implementation *impl,
				pl::utils::ObjectType type,
				const std::any &data
			);
			static pl::utils::ObjectType getObjectType(pl::Renderer::Implementation *impl, pl::utils::Id objectID);
			static void usePipeline(pl::Renderer::Implementation *impl, pl::utils::Id pipeline);
			static void drawVertices(pl::Renderer::Implementation *impl, pl::utils::Id vertices, bool forceNormalRenderMode);
			static void setUniformValues(
				pl::Renderer::Implementation *impl,
				pl::utils::Id pipeline,
				const std::string &uboName,
				const std::vector<pl::graphics::UniformFieldValue> &values
			);
			static void bindTexture(
				pl::Renderer::Implementation *impl,
				pl::utils::Id pipeline,
				pl::utils::Id texture,
				int bindingPoint
			);
			static void useFramebuffer(pl::Renderer::Implementation *impl, pl::utils::Id framebuffer);
			static pl::utils::Id getFramebufferTexture(pl::Renderer::Implementation *impl, pl::utils::Id framebuffer);
			static void setRenderMode(pl::Renderer::Implementation *impl, pl::graphics::RenderMode renderMode);
	};

} // namespace pl::impl::opengl
