#pragma once

#include <string>
#include <unordered_map>

#include "font.hpp"


#define PL_DEFAULT_FONT_FOLDER "fonts"


namespace pl
{
	class FontManager final
	{
		public:
			using SizedFonts = std::unordered_map<int, pl::Font*>;
			using NamedSizedFonts = std::unordered_map<std::string, pl::FontManager::SizedFonts>;
			using FontsPath = std::unordered_map<std::string, std::string>;

			FontManager();
			~FontManager();

			void addFont(const std::string &name, const std::string &path);

			pl::Font *getFont(const std::string &name, int size);


		private:
			pl::Font *m_addNewFont(const std::string &name, const std::string &path, int size);
		
			pl::FontManager::NamedSizedFonts m_fonts;
			pl::FontManager::FontsPath m_paths;
	};

} // namespace pl
