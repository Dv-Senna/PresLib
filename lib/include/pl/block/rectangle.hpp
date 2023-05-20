#pragma once

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	/// @brief A block that handle rectangle
	class Rectangle final : public pl::Block
	{
		public:
			/// @brief Constructor
			/// @param instance A reference to the instance of PL
			/// @param rect The position of the top left corner and the size of the rectangle
			/// @param color The color of the rectangle
			/// @param drawingType Either pl::drawingType::filled or pl::drawingType::outined
			Rectangle(
				pl::Instance &instance,
				const pl::math::Rect &rect,
				const pl::utils::Color &color = pl::utils::white,
				pl::DrawingType drawingType = pl::DrawingType::filled
			);
			~Rectangle() = default;

			virtual void render();

		
		private:
			SDL_Rect m_rect;
			pl::utils::Color m_color;
			pl::DrawingType m_drawingType;
	};

} // namespace pl::block
