#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Line final : public pl::impl::Block
	{
		public:
			Line(pl::impl::Instance *instance, const pl::math::Vec2f &start, const pl::math::Vec2f &end);
			virtual ~Line();

			virtual void render();

		private:
			pl::math::Vec2f m_start, m_end;
	};

} // namespace pl::impl::SDL2_renderer::blocks
