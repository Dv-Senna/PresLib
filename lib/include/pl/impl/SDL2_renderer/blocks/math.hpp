#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Math final : public pl::impl::Block
	{
		public:
			Math(
				pl::impl::Instance *instance,
				const std::string &equation,
				const pl::math::Vec2f &pos,
				float size,
				const pl::utils::Color &color
			);
			virtual ~Math();

			virtual void render();

		private:
			pl::math::Vec2f m_pos, m_size;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks
