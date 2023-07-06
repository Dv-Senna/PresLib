#include <stdexcept>

#include "fontManager.hpp"



namespace pl
{
	FontManager::FontManager() : m_registereds {}, m_fonts {}
	{

	}



	FontManager::~FontManager()
	{
		for (auto fonts : m_fonts)
		{
			for (auto font : fonts.second)
				delete font.second;
		}
	}



	void FontManager::add(const std::string &name, const std::string &path)
	{
		m_registereds[name] = path;
	}



	TTF_Font *FontManager::get(const std::string &name, int size)
	{
		auto it {m_registereds.find(name)};
		if (it == m_registereds.end())
			throw std::runtime_error("PL : Font '" + name + "' isn't registered");

		auto font {m_fonts[name].find(size)};
		if (font == m_fonts[name].end())
		{
			m_fonts[name][size] = new pl::Font(m_registereds[name], size);
			return m_fonts[name][size]->get();
		}

		return font->second->get();
	}



} // namespace pl
