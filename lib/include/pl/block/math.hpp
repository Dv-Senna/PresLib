#pragma once

#include <string>

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	class Math final : public pl::Block
	{
		public:
			Math(
				pl::Instance &instance,
				const std::string &latex,
				const pl::math::Vec2 &pos,
				const pl::utils::Color &color = {255, 255, 255},
				float scaleFactor = 1.0f
			);
			virtual ~Math();


			virtual void render();

			virtual void addChildren(pl::Block *block);
			virtual void removeChildren(pl::Block *block);

		
		private:
			SDL_Texture *m_texture;
			pl::math::Rect m_originalRect, m_renderRect;
	};

} // namespace pl::block
