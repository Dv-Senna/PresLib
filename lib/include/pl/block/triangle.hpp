#pragma once

#include <array>

#include <SDL2/SDL.h>

#include "../block.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	class Triangle final : public pl::Block
	{
		public:
			Triangle(
				pl::Instance &instance,
				const std::array<pl::math::Vec2, 3> &vertices,
				const pl::utils::Color &color = pl::utils::colorUndefined,
				pl::DrawingType drawingType = pl::DrawingType::filled
			);
			virtual ~Triangle() = default;

			virtual void render();


		private:
			std::array<pl::math::Vec2, 3> m_vertices;
			std::array<SDL_Vertex, 3> m_verticesSDL;
			pl::utils::Color m_color;
			pl::DrawingType m_drawingType;
	};

} // namespace pl::block