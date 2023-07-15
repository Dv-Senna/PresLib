#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"
#include "../../../renderMethod.hpp"
#include "../../../states/triangle.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Triangle final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Triangle(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &pos1,
				const pl::math::Vec2f &pos2,
				const pl::math::Vec2f &pos3,
				Args ...args
			);
			virtual ~Triangle();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			static void s_renderFillTriangle(
				SDL_Renderer *renderer,
				const pl::math::Vec2f &pos1,
				const pl::math::Vec2f &pos2,
				const pl::math::Vec2f &pos3
			);
			static void s_renderBorderTriangle(
				SDL_Renderer *renderer,
				const pl::math::Vec2f &pos1,
				const pl::math::Vec2f &pos2,
				const pl::math::Vec2f &pos3,
				float borderThickness
			);

			pl::math::Vec2f m_pos, m_size;
			pl::states::Triangle m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "triangle.inl"