#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../math/vec2.hpp"


#define PL_IMAGES_DEFAULT_FOLDER "images"


namespace pl::block
{
	class Image final : public pl::Block
	{
		public:
			Image(
				pl::Instance &instance,
				const std::string &path,
				const pl::math::Vec2 &position,
				float scaleFactor = 1.0f
			);
			~Image();


			virtual void render();

			virtual void addChildren(pl::Block *block);
			virtual void removeChildren(pl::Block *block);


		private:
			SDL_Texture *m_texture;
			pl::math::Rect m_originalRect, m_renderRect;
	};

} // namespace pl::block
