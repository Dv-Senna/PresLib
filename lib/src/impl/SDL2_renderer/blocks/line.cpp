#include <iostream>
#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/line.hpp"
#include "math/angle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Line::~Line()
	{
		this->m_unload();
	}



	void Line::render()
	{
		static SDL_FPoint center {0.f, 0.f};
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect,
			m_angle, &center, SDL_FLIP_NONE
			) != 0)
			throw std::runtime_error("PL : Can't render line texture : " + std::string(SDL_GetError()));


		this->m_renderChildren();
	}



	void Line::m_load()
	{
		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;

		constexpr float generationUpscaleFactor = 10.f;

		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;

		if (m_state.start.x <= m_state.end.x && m_state.start.y <= m_state.end.y)
			m_pos = m_state.start;

		else if (m_state.start.x >= m_state.end.x && m_state.start.y >= m_state.end.y)
			m_pos = m_state.end;

		else if (m_state.start.x <= m_state.end.x && m_state.start.y >= m_state.end.y)
			m_pos = {m_state.start.x, m_state.end.y};

		else if (m_state.start.x >= m_state.end.x && m_state.start.y <= m_state.end.y)
			m_pos = {m_state.end.x, m_state.start.y};

		m_size.x = pl::math::length(m_state.start - m_state.end) * m_state.scale * m_state.distortion.x * generationUpscaleFactor;
		m_size.y = m_state.thickness * m_state.scale * m_state.distortion.y * generationUpscaleFactor;

		if (m_size.x == 0)
			m_size.x = m_state.thickness;

		if (m_size.y == 0)
			m_size.y = m_state.thickness;


		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {SDL_CreateRGBSurfaceWithFormat(
				0, m_size.x, m_size.y, 8, SDL_PIXELFORMAT_RGBA8888
			), SDL_FreeSurface};

		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create the surface of line : " + std::string(SDL_GetError()));

	
		s_drawLine(surface.get(), m_size, m_state.startTipShape, m_state.endTipShape);
		m_angle = pl::math::toDeg(atan2(m_state.end.y - m_state.start.y, m_state.end.x - m_state.start.x));

		m_size /= generationUpscaleFactor;

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



	void Line::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



	void Line::s_drawLine(
		SDL_Surface *surface,
		const pl::math::Vec2f &size,
		pl::TipShape startTip,
		pl::TipShape endTip
	)
	{
		constexpr float antialiasingPourcentage = 0.97f;
		float a = - std::numbers::pi / (2.f * (1 - antialiasingPourcentage * antialiasingPourcentage));
		float b = -a;
		float r = size.y / 2.f;

		for (int x {0}; x < static_cast<int> (size.x); x++)
		{
			for (int y {0}; y < static_cast<int> (size.y); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::white;

				if (startTip == pl::TipShape::round && x < static_cast<int> (r))
				{
					float xoffset = r - static_cast<float> (x);
					float yoffset = static_cast<float> (y) - size.y / 2.f;
					float length = (xoffset * xoffset + yoffset * yoffset) / (r*r);
					if (length > 1.f)
						*currentPixel = pl::utils::transparent;

					else if (length > antialiasingPourcentage * antialiasingPourcentage)
					{
						int alpha = 255 * sin(a * length + b);
						*currentPixel = pl::utils::Color(255, 255, 255, alpha);
					}
				}

				if (endTip == pl::TipShape::round && x > static_cast<int> (size.x - r))
				{
					float xoffset = static_cast<float> (x) - (size.x - r);
					float yoffset = static_cast<float> (y) - size.y / 2.f;
					float length = (xoffset * xoffset + yoffset * yoffset) / (r*r);
					if (length > 1.f)
						*currentPixel = pl::utils::transparent;

					else if (length > antialiasingPourcentage * antialiasingPourcentage)
					{
						int alpha = 255 * sin(a * length + b);
						*currentPixel = pl::utils::Color(255, 255, 255, alpha);
					}
				}
			}
		}
	}



} // namespace pl::impl::SDL2_renderer::blocks
