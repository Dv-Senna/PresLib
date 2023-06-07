#pragma once

#include <string>
#include <unordered_map>

#include "font.hpp"

#include "defines.inl"


namespace pl
{
	/// @brief A manager that handle pl::Font life-cycle and load font size on the fly
	class FontManager final
	{
		public:
			using SizedFonts = std::unordered_map<int, pl::Font*>;
			using NamedSizedFonts = std::unordered_map<std::string, pl::FontManager::SizedFonts>;
			using FontsPath = std::unordered_map<std::string, std::string>;

			FontManager();
			~FontManager();

			/// @brief Register a new font. This function won't load anything into the ram
			/// @param name The name of the font
			/// @param path The path of the font relative to PL_DEFAULT_FONT_FOLDER
			void addFont(const std::string &name, const std::string &path);

			/// @brief Get register font. If name.size is not loaded, it automaticly load it
			/// @param name The name of the font
			/// @param size The size of the font
			/// @return The newly loaded font
			pl::Font *getFont(const std::string &name, int size);


		private:
			pl::Font *m_addNewFont(const std::string &name, const std::string &path, int size);
		
			pl::FontManager::NamedSizedFonts m_fonts;
			pl::FontManager::FontsPath m_paths;
	};

} // namespace pl
