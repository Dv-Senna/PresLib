#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "../block.hpp"
#include "../math/rect.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::block
{
	/// @brief A block that handle text
	class Text final : public pl::Block
	{
		public:
			/// @brief Constructor
			/// @param instance A reference to the instance of PL
			/// @param position The position of the top left corner of the text
			/// @param content The content to be displayed
			/// @param font The font used. Must have been register with instance.getFonts().addFont(...)
			/// @param size The size of the font used
			/// @param color The color of the text
			Text(
				pl::Instance &instance,
				const pl::math::Vec2 &position,
				const std::string &content,
				const std::string &font,
				int size,
				const pl::utils::Color &color = pl::utils::white
			);
			virtual ~Text();

			virtual void render();

			virtual void addChildren(pl::Block *block);
			virtual void removeChildren(pl::Block *block);


		private:
			pl::math::Rect m_rect;
			std::string m_content, m_font;
			int m_size;
			pl::utils::Color m_color;
			SDL_Texture *m_texture;
	};

} // namespace pl::block
