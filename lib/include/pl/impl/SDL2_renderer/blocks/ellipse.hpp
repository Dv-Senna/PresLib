#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"
#include "../../../renderMethod.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Ellipse final : public pl::impl::Block
	{
		public:
			Ellipse(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &center,
				float radius,
				float excentricity,
				float angle,
				const pl::utils::Color &color,
				pl::RenderMethod method
			);
			virtual ~Ellipse();

			virtual void render();

		private:
			static void s_drawFilledEllipse(
				SDL_Surface *surface,
				const pl::math::Vec2f &size
			);

			static void s_drawBorderEllipse(
				SDL_Surface *surface,
				const pl::math::Vec2f &outerSize,
				const pl::math::Vec2f &innerSize
			);

			pl::math::Vec2f m_center, m_size;
			float m_angle;
			pl::utils::Color m_color;
			pl::RenderMethod m_method;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks
