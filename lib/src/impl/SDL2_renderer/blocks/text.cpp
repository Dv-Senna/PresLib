#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/text.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Text::Text(
		pl::impl::Instance *instance,
		const std::string &text,
		const pl::math::Vec2f &pos,
		const std::string &font,
		float size,
		const pl::utils::Color &color
	) : 
		pl::impl::Block(instance),
		m_pos {pos},
		m_size {},
		m_texture {nullptr}
	{
		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TTF_RenderUTF8_Blended_Wrapped(
				m_instance->getFonts().get(font, size), text.c_str(), color, 0
			),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create text '" + text + "' with font '" + font + "' : " + std::string(TTF_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert text's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		if (SDL_SetTextureColorMod(m_texture, color.r, color.g, color.b) != 0)
			throw std::runtime_error("PL : Can't change text color : " + std::string(SDL_GetError()));

		m_size.x = surface->w;
		m_size.y = surface->h;
	}



	Text::~Text()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Text::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
		) != 0)
			throw std::runtime_error("PL : Can't render text : " + std::string(SDL_GetError()));
	}



} // namespace pl::impl::SDL2_renderer::blocks
