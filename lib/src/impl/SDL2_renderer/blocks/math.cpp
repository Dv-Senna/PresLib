#include <memory>
#include <stdexcept>

#include <SDL2/SDL_latex.h>

#include "impl/SDL2_renderer/blocks/math.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Math::Math(
		pl::impl::Instance *instance,
		const std::string &equation,
		const pl::math::Vec2f &pos,
		float size,
		const pl::utils::Color &color
	) : 
		pl::impl::Block(instance),
		m_pos {pos},
		m_size {},
		m_texture {nullptr}
	{
		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			TEX_ParseLaTeX(equation.c_str(), SDL_TRUE),
			SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't parse latex '" + equation + "' : " + std::string(TEX_GetError()));

		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get()
		);
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert math's SDL_Surface* to SDL_Texture* : " + std::string(SDL_GetError()));

		if (SDL_SetTextureColorMod(m_texture, color.r, color.g, color.b) != 0)
			throw std::runtime_error("PL : Can't change math color : " + std::string(SDL_GetError()));

		m_size.x = surface->w * size / surface->h;
		m_size.y = size;
	}



	Math::~Math()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Math::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
		) != 0)
			throw std::runtime_error("PL : Can't render math : " + std::string(SDL_GetError()));
	}



} // namespace pl::impl::SDL2_renderer::blocks
