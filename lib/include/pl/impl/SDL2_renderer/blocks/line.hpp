#pragma once

#include "../../block.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Line final : public pl::impl::Block
	{
		public:
			Line(pl::impl::Instance *instance, int startx, int starty, int endx, int endy);
			virtual ~Line();

			virtual void render();

		private:
			int m_startx, m_starty, m_endx, m_endy;
	};

} // namespace pl::impl::SDL2_renderer::blocks
