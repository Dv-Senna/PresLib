#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/line.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Line final : public pl::Block<API>
	{
		public:
			Line(pl::Instance<API> &instance, int startx, int starty, int endx, int endy) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Line(instance.getImplementation(), startx, starty, endx, endy);
			}
	};

} // namespace pl::blocks
