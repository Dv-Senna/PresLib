#pragma once

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	class Rectangle final : public pl::Block
	{
		public:
			Rectangle(
				pl::Instance &instance,
				const pl::math::Rect &rect,
				const pl::utils::Color &color = {255, 255, 255},
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
