#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/triangle.hpp"
#include "../impl/SDL2_gpu/blocks/triangle.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Triangle final : public pl::Block<API>
	{
		public:
			Triangle(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &a,
				const pl::math::Vec2f &b,
				const pl::math::Vec2f &c,
				const pl::utils::Color &color = pl::utils::white,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Triangle(instance.getImplementation(), a, b, c, color, method);

				else if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_gpu::blocks::Triangle(instance.getImplementation(), a, b, c, color, method);
			}
	};

} // namespace pl::blocks
