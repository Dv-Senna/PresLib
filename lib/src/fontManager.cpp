#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <utf8.h>

#include "fontManager.hpp"
#include "instance.hpp"



namespace pl
{
	FontManager::FontManager(pl::Instance &instance) : 
		m_instance {instance},
		m_fonts {}
	{
		if (FT_Init_FreeType(&m_ft))
			throw std::runtime_error("PL : Can't init FreeType");
	}



	FontManager::~FontManager()
	{
		for (const auto &font : m_fonts)
			FT_Done_Face(font.second.face);

		FT_Done_FreeType(m_ft);
	}



	bool FontManager::isFontRegister(const std::string &name)
	{
		return m_fonts.find(name) != m_fonts.end();
	}



	void FontManager::registerFont(const std::string &name, const std::string &fontPath)
	{
		if (this->isFontRegister(name))
			return;

		FT_Face face {};
		if (FT_New_Face(m_ft, fontPath.c_str(), 0, &face))
			throw std::runtime_error("PL : Can't load font '" + fontPath + "'");

		m_fonts[name] = {face, {}};
	}



	const pl::Character &FontManager::getCharacterInformation(const std::string &name, int size, char32_t character)
	{
		if (!this->isFontRegister(name))
			throw std::runtime_error("PL : Can't use font '" + name + "' because it has not been registered");

		pl::FontFamily &fontFamily {m_fonts[name]};

		auto &characters {fontFamily.fonts[size].characters};
		auto it {characters.find(character)};
		if (it != characters.end())
			return it->second;


		if (FT_Set_Pixel_Sizes(fontFamily.face, 0, size))
			throw std::runtime_error("PL : Can't change font size to " + std::to_string(size));

		if (FT_Load_Char(fontFamily.face, character, FT_LOAD_RENDER))
			throw std::runtime_error("PL : Can't generate bitmap of '" + std::to_string(character) + "' with font '" + name + "'");

		glm::vec2 bitmapSize {fontFamily.face->glyph->bitmap.width, fontFamily.face->glyph->bitmap.rows};
		auto bitmapBytes {std::shared_ptr<unsigned char> (new unsigned char[static_cast<size_t> (bitmapSize.x * bitmapSize.y)])};

		for (size_t i {0}; i < static_cast<size_t> (bitmapSize.x * bitmapSize.y); ++i)
			bitmapBytes.get()[i] = fontFamily.face->glyph->bitmap.buffer[i];

		auto texture = m_instance.getRenderer().registerObject(pl::utils::ObjectType::texture, pl::graphics::Texture(
			bitmapSize,
			bitmapBytes,
			pl::graphics::ColorFormat::r8
		));

		pl::Character charInfos {};
		charInfos.texture = texture;
		charInfos.size = bitmapSize;
		charInfos.bearing = glm::ivec2(fontFamily.face->glyph->bitmap_left, fontFamily.face->glyph->bitmap_top);
		charInfos.advance = fontFamily.face->glyph->advance.x / 64;

		characters[character] = charInfos;

		return characters[character];
	}



	std::vector<pl::Character> FontManager::getCharactersFromString(const std::string &name, int size, const std::string &text)
	{
		std::vector<pl::Character> characters {};
		std::vector<char32_t> utf32text {};

		(void)utf8::utf8to32(text.begin(), text.end(), std::back_inserter(utf32text));

		characters.reserve(utf32text.size());

		for (char32_t character : utf32text)
		{
			characters.push_back(this->getCharacterInformation(name, size, character));
		}

		return characters;
	}



} // namespace pl
