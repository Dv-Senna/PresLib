#include <stdexcept>

#include "defines.inl"
#include "font.hpp"



namespace pl
{
	Font::Font(const std::string &path, int size) : m_font {nullptr}
	{
		m_font = TTF_OpenFont((PL_DEFAULT_FONT_FOLDER_PATH + path).c_str(), size);
		if (m_font == nullptr)
			throw std::runtime_error("PL : Can't load font '" + path + "' : " + std::string(TTF_GetError()));
	}



	Font::~Font()
	{
		if (m_font != nullptr)
			TTF_CloseFont(m_font);
	}



} // namespace pl
