#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"
#include "../../../states/line.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Line final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Line(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &start,
				const pl::math::Vec2f &end,
				Args ...args
			);
			virtual ~Line();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			static void s_drawLine(
				SDL_Surface *surface,
				const pl::math::Vec2f &size,
				pl::TipShape startTip,
				pl::TipShape endTip
			);

			pl::math::Vec2f m_pos, m_size;
			pl::states::Line m_state;
			float m_angle;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks



#include "line.inl"