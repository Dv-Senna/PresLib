#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/rectangle.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Rectangle final : public pl::Block<API>
	{
		public:
			Rectangle(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &pos,
				const pl::math::Vec2f &size,
				const pl::utils::Color &color = pl::utils::white,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Rectangle(instance.getImplementation(), pos, size, color, method);
			}
	};

} // namespace pl::blocks
