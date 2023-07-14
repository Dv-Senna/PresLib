#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../renderMethod.hpp"
#include "../../../states/ellipse.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Ellipse final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Ellipse(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &center,
				float radius,
				Args ...args
			);
			virtual ~Ellipse() noexcept;

			virtual void render();

		private:
			void m_load();
			void m_unload() noexcept;

			static void s_drawFilledEllipse(
				SDL_Surface *surface,
				const pl::math::Vec2f &size
			);

			static void s_drawBorderEllipse(
				SDL_Surface *surface,
				const pl::math::Vec2f &outerSize,
				const pl::math::Vec2f &innerSize
			);

			pl::math::Vec2f m_size;
			pl::states::Ellipse m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks

#include "ellipse.inl"