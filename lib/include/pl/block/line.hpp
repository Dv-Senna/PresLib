#pragma once

#include "../block.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	/// @brief A block that handle line
	class Line final : public pl::Block
	{
		public:
			/// @brief Constructor
			/// @param instance A reference to the instance of PL
			/// @param start The position of the start of the line
			/// @param end The position of the end of the line
			/// @param color The color of the line
			Line(
				pl::Instance &instance,
				pl::math::Vec2 start,
				pl::math::Vec2 end,
				const pl::utils::Color color = pl::utils::white
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
