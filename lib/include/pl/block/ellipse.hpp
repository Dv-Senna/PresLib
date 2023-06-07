#pragma once

#include <array>

#include "../block.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	/// @brief A primitive class that handle circle and ellipse blocks
	class Ellipse final : public pl::Block
	{
		public:
			/// @brief Constructor of ellipse
			/// @param instance A reference to the instance of pl
			/// @param center The position of the center
			/// @param size The radius of the circle OR the length of the largest radius
			/// @param excentricity 0 for a circle, < 1.0f for an ellipse
			/// @param color The color of the ellipse
			/// @param drawingType Either pl::drawingType::filled or pl::drawingType::outlined
			Ellipse(
				pl::Instance &instance,
				const pl::math::Vec2 &center,
				float size,
				float excentricity = 0.0f,
				const pl::utils::Color &color = pl::utils::colorUndefined,
				pl::DrawingType drawingType = pl::DrawingType::filled
			);
			virtual ~Ellipse() = default;

			/// @brief Invert the width and the height of the ellipse
			void flipWidthAndHeight(bool flip = true);

			virtual void render();

		private:
			static std::array<float, 12> s_vertices;

			pl::math::Vec2 m_center, m_size;
			float m_excentricity;
			pl::utils::Color m_color;
			pl::DrawingType m_drawingType;
			bool m_flipWidthAndheight;
	};

} // namespace pl::block
