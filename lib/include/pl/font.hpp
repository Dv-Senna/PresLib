#pragma once

#include <string>

#include <SDL2_ttf/SDL_ttf.h>


namespace pl
{
	class Font final
	{
		public:
			Font(const std::string &path, int size);
			~Font();

			inline TTF_Font *getFont() const noexcept {return m_font;}
			inline int getSize() const noexcept {return m_size;}


		private:
			TTF_Font *m_font;
			int m_size;
	};

} // namespace pl
