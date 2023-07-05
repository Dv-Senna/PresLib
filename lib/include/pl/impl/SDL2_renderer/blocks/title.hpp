#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Title final : public pl::impl::Block
	{
		public:
			Title(
				pl::impl::Instance *instance,
				const std::string &text
			);
			virtual ~Title();

			virtual void render();

		private:
			pl::math::Vec2f m_pos, m_size;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks
