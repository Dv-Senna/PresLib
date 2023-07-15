#include <memory>
#include <stdexcept>

#include <SDL2/SDL_latex.h>

#include "impl/SDL2_renderer/blocks/math.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Math::~Math()
	{
		this->m_unload();
	}



	void Math::render()
	{
		SDL_FRect rect {m_state.position.x, m_state.position.y, m_size.x, m_size.y};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect,
			m_state.angle, nullptr, SDL_FLIP_NONE
		) != 0)
			throw std::runtime_error("PL : Can't render math : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



	void Math::m_load()
	{
		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.textColor;

		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TEX_ParseLaTeX(m_state.equation.c_str(), SDL_TRUE, m_state.size),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't parse latex '" + m_state.equation + "' : " + std::string(TEX_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert math's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		if (SDL_SetTextureColorMod(m_texture, m_state.color.r, m_state.color.g, m_state.color.b) != 0)
			throw std::runtime_error("PL : Can't change math color : " + std::string(SDL_GetError()));

		if (SDL_SetTextureAlphaMod(m_texture, m_state.color.a) != 0)
			throw std::runtime_error("PL : Can't change math alpha : " + std::string(SDL_GetError()));

		m_size.x = surface->w * m_state.distortion.x;
		m_size.y = surface->h * m_state.distortion.y;
	}



	void Math::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



} // namespace pl::impl::SDL2_renderer::blocks
