#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>


namespace pl
{
	/// @brief A class that handle font
	class Font final
	{
		public:
			/// @brief Constructor
			/// @param path The path of the loaded font relative to PL_DEFAULT_FONT_FOLDER
			/// @param size The size of the loaded font
			Font(const std::string &path, int size);
			~Font();

			inline TTF_Font *getFont() const noexcept {return m_font;}
			inline int getSize() const noexcept {return m_size;}


		private:
			TTF_Font *m_font;
			int m_size;
	};

} // namespace pl
