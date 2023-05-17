#pragma once

#include "../block.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	class Line final : public pl::Block
	{
		public:
			Line(
				pl::Instance &instance,
				pl::math::Vec2 start,
				pl::math::Vec2 end,
				const pl::utils::Color color = {255, 255, 255}
			);
			~Line() = default;

			virtual void render();
			virtual void addChildren(pl::Block *block);
			virtual void removeChildren(pl::Block *block);


		private:
			pl::math::Vec2 m_start, m_end;
			pl::utils::Color m_color;
	};

} // namespace pl::block
