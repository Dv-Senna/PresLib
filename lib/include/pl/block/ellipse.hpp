#pragma once

#include "../block.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	class Ellipse final : public pl::Block
	{
		public:
			Ellipse(
				pl::Instance &instance,
				const pl::math::Vec2 &center,
				float size,
				float excentricity = 0.0f,
				const pl::utils::Color &color = pl::utils::white,
				pl::DrawingType drawingType = pl::DrawingType::filled
			);
			virtual ~Ellipse() = default;

			void flipWidthAndHeight();

			virtual void render();

		private:
			pl::math::Vec2 m_center, m_size;
			float m_excentricity;
			pl::utils::Color m_color;
			pl::DrawingType m_drawingType;
	};

} // namespace pl::block
