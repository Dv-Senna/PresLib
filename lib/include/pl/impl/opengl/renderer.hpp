#pragma once

#include "../../renderer.hpp"


namespace pl::impl::opengl
{
	class Renderer
	{
		public:
			static void setup(pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &createInfo);
			static void cleanup(pl::Renderer::Implementation *impl);
			static void cleanViewport(pl::Renderer::Implementation *impl, const pl::utils::Color &color);
			static void updateScreen(pl::Renderer::Implementation *impl);
	};

} // namespace pl::impl::opengl
