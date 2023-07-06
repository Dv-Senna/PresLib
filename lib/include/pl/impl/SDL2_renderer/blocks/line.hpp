#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Line final : public pl::impl::Block
	{
		public:
			Line(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &start,
				const pl::math::Vec2f &end,
				const pl::utils::Color &color
			);
			virtual ~Line();

			virtual void render();

		private:
			pl::math::Vec2f m_start, m_end;
			pl::utils::Color m_color;
	};

} // namespace pl::impl::SDL2_renderer::blocks
