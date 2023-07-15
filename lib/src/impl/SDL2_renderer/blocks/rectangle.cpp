#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/rectangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Rectangle::~Rectangle()
	{
		this->m_unload();
	}



	void Rectangle::render()
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



	void Rectangle::m_load()
	{
		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;

		m_size.x = m_state.size.x * m_state.scale * m_state.distortion.x;
		m_size.y = m_state.size.y * m_state.scale * m_state.distortion.y;
		m_borderThickness.x = m_state.borderThickness * m_state.scale * m_state.distortion.x;
		m_borderThickness.y = m_state.borderThickness * m_state.scale * m_state.distortion.y;
		
		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {SDL_CreateRGBSurfaceWithFormat(
				0, m_size.x, m_size.y, 8, SDL_PIXELFORMAT_RGBA8888
			), SDL_FreeSurface};

		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create the surface of line : " + std::string(SDL_GetError()));


		if (m_state.renderMethod == pl::RenderMethod::fill)
			s_renderFillRectangle(surface.get(), m_size);

		else if (m_state.renderMethod == pl::RenderMethod::border)
			s_renderBorderRectangle(surface.get(), m_size, m_borderThickness);


		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			surface.get()
		);

		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert the surface of line in texture : " + std::string(SDL_GetError()));

		if (SDL_SetTextureColorMod(m_texture, m_state.color.r, m_state.color.g, m_state.color.b) != 0)
			throw std::runtime_error("PL : Can't set line's texture color mod : " + std::string(SDL_GetError()));

		if (SDL_SetTextureAlphaMod(m_texture, m_state.color.a) != 0)
			throw std::runtime_error("PL : Can't set line's texture alpha mod : " + std::string(SDL_GetError()));
	}



	void Rectangle::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



	void Rectangle::s_renderFillRectangle(
		SDL_Surface *surface,
		const pl::math::Vec2f &size
	)
	{
		for (int x {0}; x < static_cast<int> (size.x); x++)
		{
			for (int y {0}; y < static_cast<int> (size.y); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::white;
			}
		}
	}



	void Rectangle::s_renderBorderRectangle(
		SDL_Surface *surface,
		const pl::math::Vec2f &size,
		const pl::math::Vec2f &borderThickness
	)
	{
		for (int x {0}; x < static_cast<int> (size.x); x++)
		{
			for (int y {0}; y < static_cast<int> (size.y); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::white;

				if (
					x > static_cast<int> (borderThickness.x)
					&& x < static_cast<int> (size.x - borderThickness.x)
					&& y > static_cast<int> (borderThickness.y)
					&& y < static_cast<int> (size.y - borderThickness.y)
				)
					*currentPixel = pl::utils::transparent;
			}
		}
	}



} // namespace pl::impl::SDL2_renderer::blocks
