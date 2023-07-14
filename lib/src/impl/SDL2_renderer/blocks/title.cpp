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
		m_size {},
		m_state {text},
		m_texture {nullptr}
	{
		const pl::Style &style {m_instance->getTheme().style};

		m_state.position = style.titlePosition;
		m_state.size = style.titleSize;
		m_state.color = style.titleColor;

		this->m_load();
	}



	Title::~Title()
	{
		this->m_unload();
	}



	void Title::render()
	{
		SDL_FRect rect {m_state.position.x, m_state.position.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
		) != 0)
			throw std::runtime_error("PL : Can't render text : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



	void Title::m_load()
	{
		const pl::Style &style {m_instance->getTheme().style};

		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TTF_RenderUTF8_Blended_Wrapped(
				m_instance->getFonts().get(style.titleFont, m_state.size), m_state.text.c_str(), m_state.color, 0
			),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create title '" + m_state.text + "' : " + std::string(TTF_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert title's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		m_size.x = surface->w * m_state.distortion.x;
		m_size.y = surface->h * m_state.distortion.y;
	}



	void Title::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



} // namespace pl::impl::SDL2_renderer::blocks
