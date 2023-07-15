#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../renderMethod.hpp"
#include "../../../states/rectangle.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Rectangle final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Rectangle(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &pos,
				const pl::math::Vec2f &size,
				Args ...args
			);
			virtual ~Rectangle();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			static void s_renderFillRectangle(
				SDL_Surface *surface,
				const pl::math::Vec2f &size
			);
			static void s_renderBorderRectangle(
				SDL_Surface *surface,
				const pl::math::Vec2f &size,
				const pl::math::Vec2f &borderThickness
			);

			pl::states::Rectangle m_state;
			pl::math::Vec2f m_size;
			pl::math::Vec2f m_borderThickness;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "rectangle.inl"