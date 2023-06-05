#include <cassert>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL_image.h>

#include "block/image.hpp"



namespace pl::block
{
	Image::Image(
		pl::Instance &instance,
		const std::string &path,
		const pl::math::Vec2 &position,
		float scaleFactor
	) : 
		pl::Block(instance),
		m_texture {nullptr},
		m_originalRect {position.x, position.y, 0, 0},
		m_renderRect {position.x, position.y, 0, 0}
	{
		std::string fullPath = std::string(PL_DEFAULT_IMAGES_FOLDER) + "/" + path;

		auto surface = std::unique_ptr<
			SDL_Surface,
			decltype([](auto *ptr) {SDL_FreeSurface(ptr);})
		> (IMG_Load(fullPath.c_str()));

		if (surface == nullptr)
			throw std::runtime_error("PL : Can't load image '" + fullPath + "' : " + std::string(IMG_GetError()));

		m_originalRect.w = surface->w;
		m_originalRect.h = surface->h;
		m_renderRect.w = m_originalRect.w * scaleFactor;
		m_renderRect.h = m_originalRect.h * scaleFactor;

		m_texture = SDL_CreateTextureFromSurface(m_instance.getRenderer(), surface.get());
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert surface image to texture : " + std::string(IMG_GetError()));
	}



	Image::~Image()
	{
		SDL_DestroyTexture(m_texture);
	}



	void Image::render()
	{
		SDL_Rect rect = m_renderRect;

		if (SDL_RenderCopy(m_instance.getRenderer(), m_texture, nullptr, &rect) != 0)
			throw std::runtime_error("PL : Can't render image : " + std::string(SDL_GetError()));
	}



	void Image::addChildren(pl::Block *block)
	{
		assert(block && "PL : don't call addChildren on an image block");
	}



	void Image::removeChildren(pl::Block *block)
	{
		assert(block && "PL : don't call removeChildren on an image block");
	}




} // namespace pl::block
