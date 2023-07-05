#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/title.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Title::Title(
		pl::impl::Instance *instance,
		const std::string &text
	) : 
		pl::impl::Block(instance),
		m_pos {},
		m_size {},
		m_texture {nullptr}
	{
		const pl::Style &style {m_instance->getTheme().style};

		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TTF_RenderUTF8_Blended_Wrapped(
				m_instance->getFonts().get(style.titleFont, style.titleSize), text.c_str(), style.titleColor, 0
			),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create title '" + text + "' : " + std::string(TTF_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert title's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		m_size.x = surface->w;
		m_size.y = surface->h;

		m_pos = style.titlePosition;
	}



	Title::~Title()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Title::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
		) != 0)
			throw std::runtime_error("PL : Can't render text : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



} // namespace pl::impl::SDL2_renderer::blocks
