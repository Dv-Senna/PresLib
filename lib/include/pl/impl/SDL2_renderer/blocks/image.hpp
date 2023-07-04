#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Image final : public pl::impl::Block
	{
		public:
			Image(
				pl::impl::Instance *instance,
				const std::string &path,
				const pl::math::Vec2f &pos,
				float scale
			);
			virtual ~Image();

			virtual void render();

		private:
			pl::math::Vec2f m_pos, m_size;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks
