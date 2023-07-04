#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>


namespace pl
{
	class Font final
	{
		public:
			Font(const std::string &path, int size);
			~Font();

			inline TTF_Font *get() const noexcept {return m_font;}


		private:
			TTF_Font *m_font;
	};

} // namespace pl
