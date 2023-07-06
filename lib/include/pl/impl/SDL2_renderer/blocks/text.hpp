#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Text final : public pl::impl::Block
	{
		public:
			Text(
				pl::impl::Instance *instance,
				const std::string &text,
				const pl::math::Vec2f &pos,
				const std::string &font,
				float size,
				const pl::utils::Color &color
			);
			virtual ~Text();

			virtual void render();

		private:
			pl::math::Vec2f m_pos, m_size;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks
