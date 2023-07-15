#include <iostream>
#include <memory>
#include <stdexcept>

#include "impl/SDL2_renderer/blocks/line.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Line::~Line()
	{
		this->m_unload();
	}



	void Line::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect
			) != 0)
			throw std::runtime_error("PL : Can't render line texture : " + std::string(SDL_GetError()));



		this->m_renderChildren();
	}



	void Line::m_load()
	{
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

		std::cout << m_pos << std::endl;

		m_size.x = abs(m_state.end.x - m_state.start.x);
		m_size.y = abs(m_state.end.y - m_state.start.y);

		if (m_size.x == 0)
			m_size.x = m_state.thickness;

		if (m_size.y == 0)
			m_size.y = m_state.thickness;


		std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface {SDL_CreateRGBSurfaceWithFormat(
				0, m_size.x, m_size.y, 8, SDL_PIXELFORMAT_RGBA8888
			), SDL_FreeSurface};

		if (surface.get() == nullptr)
			throw std::runtime_error("PL : Can't create the surface of line : " + std::string(SDL_GetError()));

		
		if (m_size.x == m_state.thickness || m_size.y == m_state.thickness)
			s_drawHorizontalOrVerticalLine(surface.get(), m_size);

		else
		{
			s_drawDiagonalLine(
				surface.get(),
				m_state.start,
				m_state.end,
				m_state.thickness,
				m_size,
				m_state.startTipShape,
				m_state.endTipShape
			);
		}


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



	void Line::s_drawHorizontalOrVerticalLine(
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



	void Line::s_drawDiagonalLine(
		SDL_Surface *surface,
		const pl::math::Vec2f &start,
		const pl::math::Vec2f &end,
		float thickness,
		const pl::math::Vec2f &size,
		pl::TipShape startTip,
		pl::TipShape endTip
	)
	{
		constexpr float antialiasingPourcentage {0.97f};

		const float b = (end.x - start.x) / (start.y - end.y);
		const float c = (start.x * end.y - end.x * start.y) / (end.y - start.y);
		const float incertitude = abs(start.x + b * start.y + .5f * sqrt(1 + b*b) * thickness - c);
		const float antiA = 1.f / (antialiasingPourcentage - 1.f);
		const float antiB = - antiA;

		for (int x {0}; x < static_cast<int> (size.x); x++)
		{
			for (int y {0}; y < static_cast<int> (size.y); y++)
			{
				uint32_t *currentPixel = reinterpret_cast <uint32_t*> (static_cast<uint8_t*> (
					surface->pixels
				) + y * surface->pitch + x * surface->format->BytesPerPixel);

				*currentPixel = pl::utils::transparent;
				const float length = x + b * y - c;

				if (length >= -incertitude * antialiasingPourcentage && length <= incertitude * antialiasingPourcentage)
					*currentPixel = pl::utils::white;

				else if (length >= -incertitude && length <= incertitude * antialiasingPourcentage)
				{
					const int alpha = (antiA * abs(length) + antiB) * 255.f;
					*currentPixel = pl::utils::Color(255, 255, 255, alpha);
				}

				else if (length >= -incertitude * antialiasingPourcentage && length <= incertitude)
				{
					const int alpha = (antiA * abs(length) + antiB) * 255.f;
					*currentPixel = pl::utils::Color(255, 255, 255, alpha);
				}
			}
		}
	}



} // namespace pl::impl::SDL2_renderer::blocks
