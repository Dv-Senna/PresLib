#include <cassert>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_latex.h>

#include "block/math.hpp"



namespace pl::block
{
	
	Math::Math(
		pl::Instance &instance,
		const std::string &latex,
		const pl::math::Vec2 &pos,
		float scaleFactor
	) :
		pl::Block(instance),
		m_texture {nullptr},
		m_originalRect {pos.x, pos.y, 0, 0},
		m_renderRect {pos.x, pos.y, 0, 0}
	{
		auto surface = std::unique_ptr<
			SDL_Surface,
			decltype([](auto *ptr) {SDL_FreeSurface(ptr);})
		> (TEX_ParseLaTeX(latex.c_str(), SDL_TRUE));

		if (surface == nullptr)
			throw std::runtime_error("PL : Can't parse LaTeX '" + latex + "' : " + std::string(TEX_GetError()));

		m_originalRect.w = surface->w;
		m_originalRect.h = surface->h;
		m_renderRect.w = m_originalRect.w * scaleFactor;
		m_renderRect.h = m_originalRect.h * scaleFactor;

		m_texture = SDL_CreateTextureFromSurface(m_instance.getRenderer(), surface.get());
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert surface latex to texture : " + std::string(SDL_GetError()));
	}



	Math::~Math()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Math::render()
	{
		SDL_Rect rect = m_renderRect;

		if (SDL_RenderCopy(m_instance.getRenderer(), m_texture, nullptr, &rect) != 0)
			throw std::runtime_error("PL : Can't render image : " + std::string(SDL_GetError()));
	}



	void Math::addChildren(pl::Block *block)
	{
		assert(block && "PL : don't call addChildren on an image block");
	}



	void Math::removeChildren(pl::Block *block)
	{
		assert(block && "PL : don't call removeChildren on an image block");
	}





} // namespace pl::block
