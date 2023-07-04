#include <memory>
#include <stdexcept>

#include <SDL2/SDL_image.h>

#include "defines.inl"
#include "impl/SDL2_renderer/blocks/image.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Image::Image(
		pl::impl::Instance *instance,
		const std::string &path,
		const pl::math::Vec2f &pos,
		float scale
	) : 
		pl::impl::Block(instance),
		m_pos {pos},
		m_size {},
		m_texture {nullptr}
	{
		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			IMG_Load((PL_DEFAULT_IMAGE_FOLDER_PATH + path).c_str()), SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't load image '" + path + "' : " + std::string(IMG_GetError()));

		m_size.x = surface->w * scale;
		m_size.y = surface->h * scale;

		m_texture = SDL_CreateTextureFromSurface(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get());
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert image surface to texture : " + std::string(SDL_GetError()));
	}



	Image::~Image()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



	void Image::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
		) != 0)
			throw std::runtime_error("PL : Can't render image : " + std::string(SDL_GetError()));
	}



} // namespace pl::impl::SDL2_renderer::blocks
