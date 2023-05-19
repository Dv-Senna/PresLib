#include <cassert>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "block/text.hpp"



namespace pl::block
{
	Text::Text(
		pl::Instance &instance,
		const pl::math::Vec2 &position,
		const std::string &content,
		const std::string &font,
		int size,
		const pl::utils::Color &color
	) : 
		pl::Block(instance),
		m_rect {position.x, position.y, 0, 0},
		m_content {content},
		m_font {font},
		m_size {size},
		m_color {color},
		m_texture {nullptr}
	{
		auto surface = std::unique_ptr<
			SDL_Surface,
			decltype([](auto *ptr) {SDL_FreeSurface(ptr);})
		> (TTF_RenderText_Solid(
			m_instance.getFonts().getFont(m_font, size)->getFont(),
			m_content.c_str(),
			m_color
		));

		if (surface == nullptr)
			throw std::runtime_error("PL : Can't load text : " + std::string(TTF_GetError()));

		m_rect.w = surface->w;
		m_rect.h = surface->h;

		m_texture = SDL_CreateTextureFromSurface(m_instance.getRenderer(), surface.get());
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert text surface to texture : " + std::string(SDL_GetError()));
	}



	Text::~Text()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Text::render()
	{
		static SDL_Rect rect = m_rect;

		if (SDL_RenderCopy(m_instance.getRenderer(), m_texture, nullptr, &rect) != 0)
			throw std::runtime_error("PL : Can't render text : " + std::string(SDL_GetError()));
	}



	void Text::addChildren(pl::Block *block)
	{
		assert(block && "PL : don't call addChildren on a text block");
	}



	void Text::removeChildren(pl::Block *block)
	{
		assert(block && "PL : don't call removeChildren on a text block");
	}



} // namespace pl::block
