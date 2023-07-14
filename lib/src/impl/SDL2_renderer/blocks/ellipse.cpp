#include <iostream>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

#include "impl/SDL2_renderer/blocks/ellipse.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Ellipse::~Ellipse() noexcept
	{
		this->m_unload();
	}



	void Ellipse::render()
	{
		SDL_FRect rect {
			m_state.center.x - m_size.x, m_state.center.y - m_size.y,
			m_size.x * 2.0f, m_size.y * 2.0f
		};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect, m_state.angle, nullptr, SDL_FLIP_NONE
			) != 0)
			throw std::runtime_error("PL : Can't render ellipse texture : " + std::string(SDL_GetError()));



		this->m_renderChildren();
	}



	void Ellipse::m_load()
	{
		m_size = {m_state.radius, m_state.radius * sqrt(1 - m_state.excentricity * m_state.excentricity)};

		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;

		const pl::math::Vec2f innerBorder {m_size.x - m_state.borderThickness, m_size.y - m_state.borderThickness};

		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {SDL_CreateRGBSurfaceWithFormat(
				0, m_size.x * 2, m_size.y * 2, 8, SDL_PIXELFORMAT_RGBA8888
			), SDL_FreeSurface};

		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create the surface of ellispe : " + std::string(SDL_GetError()));


		if (m_state.drawingMethod == pl::RenderMethod::fill)
			s_drawFilledEllipse(surface.get(), m_size);

		else if (m_state.drawingMethod == pl::RenderMethod::border)
			s_drawBorderEllipse(surface.get(), m_size, innerBorder);


		m_texture = SDL_CreateTextureFromSurface(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			surface.get()
		);

		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't convert the surface of ellispe in texture : " + std::string(SDL_GetError()));

		if (SDL_SetTextureColorMod(m_texture, m_state.color.r, m_state.color.g, m_state.color.b) != 0)
			throw std::runtime_error("PL : Can't set ellipse's texture color mod : " + std::string(SDL_GetError()));

		if (SDL_SetTextureAlphaMod(m_texture, m_state.color.a) != 0)
			throw std::runtime_error("PL : Can't set ellipse's texture alpha mod : " + std::string(SDL_GetError()));
	}



	void Ellipse::m_unload() noexcept
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



	void Ellipse::s_drawFilledEllipse(
		SDL_Surface *surface,
		const pl::math::Vec2f &size
	)
	{
		constexpr float antialiasingPourcentage {0.97f};
		float a = - M_PI / (2.f * (1 - antialiasingPourcentage * antialiasingPourcentage));
		float b = -a;

		for (int x {0}; x < static_cast<int> (size.x * 2.0f); x++)
		{
			for (int y {0}; y < static_cast<int> (size.y * 2.0f); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::transparent;
				
				float xoffset = static_cast<float> (x) - size.x;
				float yoffset = static_cast<float> (y) - size.y;
				float length = xoffset * xoffset / size.x / size.x + yoffset * yoffset / size.y / size.y;

				if (length <= antialiasingPourcentage * antialiasingPourcentage)
					*currentPixel = pl::utils::white;

				else if (length <= 1.0f)
				{
					int alpha = 255 * sin(a * length + b);
					*currentPixel = pl::utils::Color(255, 255, 255, alpha);
				}
			}
		}
	}



	void Ellipse::s_drawBorderEllipse(
		SDL_Surface *surface,
		const pl::math::Vec2f &outerSize,
		const pl::math::Vec2f &innerSize
	)
	{
		constexpr float maxAntialiasingPourcentage {0.97f};
		float outerAntialiasingPourcentage = maxAntialiasingPourcentage;
		float innerAntialiasingPourcentage = 2.f - maxAntialiasingPourcentage;

		/*
		// this section is not working as indented

		if (outerSize.x * outerSize.y * outerAntialiasingPourcentage
			< innerSize.x * innerSize.y * innerAntialiasingPourcentage
		)
		{
			outerAntialiasingPourcentage = (outerSize.x * outerSize.y + innerSize.x * innerSize.y)
				/ (2.f * outerSize.x * outerSize.y);
			innerAntialiasingPourcentage = (outerSize.x * outerSize.y + innerSize.x * innerSize.y)
				/ (2.f * innerSize.x * innerSize.y);
		}*/

		float outerA = - M_PI / (2.f * (1 - outerAntialiasingPourcentage * outerAntialiasingPourcentage));
		float outerB = -outerA;
		float innerA = - M_PI / (2.f * (1 - innerAntialiasingPourcentage * innerAntialiasingPourcentage));
		float innerB = -innerA;


		for (int x {0}; x < static_cast<int> (outerSize.x * 2.0f); x++)
		{
			for (int y {0}; y < static_cast<int> (outerSize.y * 2.0f); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::transparent;

				float xoffset = static_cast<float> (x) - outerSize.x;
				float yoffset = static_cast<float> (y) - outerSize.y;
				float outerLength = xoffset * xoffset / outerSize.x / outerSize.x + yoffset * yoffset / outerSize.y / outerSize.y;
				float innerLength = xoffset * xoffset / innerSize.x / innerSize.x + yoffset * yoffset / innerSize.y / innerSize.y;

				if (outerLength <= outerAntialiasingPourcentage * outerAntialiasingPourcentage
					&& innerLength >= innerAntialiasingPourcentage * innerAntialiasingPourcentage
				)
					*currentPixel = pl::utils::white;

				else if (outerLength <= 1.f
					&& innerLength >= innerAntialiasingPourcentage * innerAntialiasingPourcentage
				)
				{
					int alpha = 255 * sin(outerA * outerLength + outerB);
					*currentPixel = pl::utils::Color(255, 255, 255, alpha);
				}

				else if (outerLength <= outerAntialiasingPourcentage * outerAntialiasingPourcentage
					&& innerLength >= 1.f
				)
				{
					int alpha = 255 * sin(innerA * innerLength + innerB);
					*currentPixel = pl::utils::Color(255, 255, 255, alpha);
				}
			}
		}
	}



} // namespace pl::impl::SDL2_renderer::blocks
