#include <stdexcept>

#include "font.hpp"



namespace pl
{
	Font::Font(const std::string &path, int size) : m_font {nullptr}, m_size {size}
	{
		m_font = TTF_OpenFont(path.c_str(), m_size);
		if (m_font == nullptr)
			throw std::runtime_error("PL : Can't open font '" + path + "' : " + std::string(TTF_GetError()));
	}



	Font::~Font()
	{
		if (m_font != nullptr)
		{
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}



} // namespace pl
