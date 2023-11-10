#pragma once

#include <cinttypes>
#include <map>
#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include "utils/id.hpp"



namespace pl
{
	struct Instance;

	struct Character
	{
		pl::utils::Id texture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	struct Font
	{
		std::map<char32_t, pl::Character> characters;
	};

	struct FontFamily
	{
		FT_Face face;
		std::map<int, pl::Font> fonts;
	};

	class FontManager
	{
		public:
			FontManager(pl::Instance &instance);
			~FontManager();

			bool isFontRegister(const std::string &name);
			void registerFont(const std::string &name, const std::string &fontPath);
			const pl::Character &getCharacterInformation(const std::string &name, int size, char32_t character);
			std::vector<pl::Character> getCharactersFromString(const std::string &name, int size, const std::string &text);


		private:
			FT_Library m_ft;
			pl::Instance &m_instance;
			std::map<std::string, pl::FontFamily> m_fonts;
	};

} // namespace pl
