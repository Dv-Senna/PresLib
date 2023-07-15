#include <memory>
#include <stdexcept>

#include <SDL2/SDL_image.h>

#include "defines.inl"
#include "impl/SDL2_renderer/blocks/image.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Image::~Image()
	{
		this->m_unload();
	}



	void Image::render()
	{
		SDL_FRect rect {m_state.position.x, m_state.position.y, m_size.x, m_size.y};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect,
			m_state.angle, nullptr, SDL_FLIP_NONE
		) != 0)
			throw std::runtime_error("PL : Can't render image : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



	void Image::m_load()
	{
		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {
			IMG_Load((PL_DEFAULT_IMAGE_FOLDER_PATH + m_state.path).c_str()), SDL_FreeSurface
		};
		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't load image '" + m_state.path + "' : " + std::string(IMG_GetError()));

		m_size.x = surface->w * m_state.scale * m_state.distortion.x;
		m_size.y = surface->h * m_state.scale * m_state.distortion.y;

		m_texture = SDL_CreateTextureFromSurface(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), surface.get());
		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert image surface to texture : " + std::string(SDL_GetError()));

		if (SDL_SetTextureAlphaMod(m_texture, 255.f * m_state.opacity) != 0)
			throw std::runtime_error("PL : Can't apply alpha value to image : " + std::string(SDL_GetError()));
	}



	void Image::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



} // namespace pl::impl::SDL2_renderer::blocks
