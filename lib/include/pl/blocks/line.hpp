#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/line.hpp"
#include "../math/vector.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Line final : public pl::Block<API>
	{
		public:
			Line(pl::Instance<API> &instance, const pl::math::Vec2f &start, const pl::math::Vec2f &end) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Line(instance.getImplementation(), start, end);
			}
	};

} // namespace pl::blocks
