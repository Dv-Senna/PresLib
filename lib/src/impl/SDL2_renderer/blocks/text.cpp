#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/text.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Text::~Text()
	{
		this->m_unload();
	}



	void Text::render()
	{
		SDL_FRect rect {m_state.position.x, m_state.position.y, m_size.x, m_size.y};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect,
			m_state.angle, nullptr, SDL_FLIP_NONE
		) != 0)
			throw std::runtime_error("PL : Can't render text : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



	void Text::m_load()
	{
		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.textColor;

		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TTF_RenderUTF8_Blended_Wrapped(
				m_instance->getFonts().get(m_state.font, m_state.size), m_state.text.c_str(), m_state.color, 0
			),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create text '" + m_state.text + "' with font '" + m_state.font + "' : " + std::string(TTF_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert text's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		m_size.x = surface->w * m_state.distortion.x;
		m_size.y = surface->h * m_state.distortion.y;
	}



	void Text::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



} // namespace pl::impl::SDL2_renderer::blocks
