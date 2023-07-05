#pragma once

#include <string>
#include <unordered_map>

#include "font.hpp"


namespace pl
{
	class FontManager final
	{
		public:
			FontManager();
			~FontManager();

			/// @brief Register a new font in the manager
			/// @param name The name of the font
			/// @param path The path to the font relative to `PL_DEFAULT_FONT_FOLDER_PATH`
			void add(const std::string &name, const std::string &path);
			/// @brief Get the wanted font with the wanted size. Lazy load the wanted configuration
			/// @param name The name used when the font was registered
			/// @param size The size of the font in px
			/// @return The font in a format readable by SDL_ttf
			TTF_Font *get(const std::string &name, int size);


		private:
			std::unordered_map<std::string, std::string> m_registereds;
			std::unordered_map<std::string, std::unordered_map<int, pl::Font*>> m_fonts;
	};

} // namespace pl
