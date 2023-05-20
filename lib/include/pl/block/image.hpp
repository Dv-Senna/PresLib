#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../math/vec2.hpp"

#include "defines.inl"


namespace pl::block
{
	/// @brief A block that handle image
	class Image final : public pl::Block
	{
		public:
			/// @brief Constructor
			/// @param instance A reference to the instance of PL
			/// @param path The path to the image to use relative to PL_IMAGES_DEFAULT_FOLDER
			/// @param position The position of the top left corner of the image
			/// @param scaleFactor A factor by witch the original image size is multiplied
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
