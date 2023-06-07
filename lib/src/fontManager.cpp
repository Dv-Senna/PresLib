#include <stdexcept>

#include "fontManager.hpp"



namespace pl
{
	FontManager::FontManager() : m_fonts {}, m_paths {}
	{

	}



	FontManager::~FontManager()
	{
		for (auto sizedFont : m_fonts)
		{
			for (auto font : sizedFont.second)
				delete font.second;
		}
	}



	void FontManager::addFont(const std::string &name, const std::string &path)
	{
		m_paths[name] = std::string(PL_DEFAULT_FONT_FOLDER) + "/" + path;
	}



	pl::Font *FontManager::getFont(const std::string &name, int size)
	{
		auto fontPath {m_paths.find(name)};
			if (fontPath == m_paths.end())
				throw std::runtime_error("PL : Font '" + name + "' doesn't exist");

		auto sizedFont {m_fonts.find(name)};
		if (sizedFont == m_fonts.end())
			return m_addNewFont(name, fontPath->second, size);


		auto font {sizedFont->second.find(size)};
		if (font == sizedFont->second.end())
			return m_addNewFont(name, fontPath->second, size);

		return font->second;
	}



	pl::Font *FontManager::m_addNewFont(const std::string &name, const std::string &path, int size)
	{
		pl::Font *newFont = new pl::Font(path, size);
		m_fonts[name][size] = newFont;
		return newFont;
	}



} // namespace pl
