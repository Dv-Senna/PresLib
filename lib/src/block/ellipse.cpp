#include <cassert>
#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>

#include "block/ellipse.hpp"



namespace pl::block
{
	Ellipse::Ellipse(
		pl::Instance &instance,
		const pl::math::Vec2 &center,
		float size,
		float excentricity,
		const pl::utils::Color &color,
		pl::DrawingType drawingType
	) : 
		pl::Block(instance),
		m_center {center},
		m_size {size, size},
		m_excentricity {excentricity},
		m_color {color},
		m_drawingType {drawingType}
	{
		assert(m_excentricity < 1.0f && "PL : excentricity must be less than 1.0f");

		if (m_excentricity != 0)
		{
			m_size.x = m_size.x / m_excentricity;
			m_size.y = m_size.y * m_size.y * (1 / (m_excentricity * m_excentricity) - 1);
		}

		if (m_color.undefined)
			m_color = m_instance.getColors().getScheme().object;
	}



	void Ellipse::flipWidthAndHeight()
	{
		float temp = m_size.x;
		m_size.x = m_size.y;
		m_size.y = temp;
	}



	void Ellipse::render()
	{
		if (m_excentricity == 0.0f)
		{
			if (m_drawingType == pl::DrawingType::filled)
			{
				if (filledCircleRGBA(
					m_instance.getRenderer(),
					m_center.x, m_center.y, m_size.x,
					m_color.r, m_color.g, m_color.b, m_color.a) != 0)
					throw std::runtime_error("PL : Can't draw a filled circle : " + std::string(SDL_GetError()));
			}

			else if (m_drawingType == pl::DrawingType::outlined)
			{
				if (aacircleRGBA(
					m_instance.getRenderer(),
					m_center.x, m_center.y, m_size.x,
					m_color.r, m_color.g, m_color.b, m_color.a) != 0)
					throw std::runtime_error("PL : Can't draw an outlined circle : " + std::string(SDL_GetError()));
			}
		}

		else
		{
			if (m_drawingType == pl::DrawingType::filled)
			{
				if (filledEllipseRGBA(
					m_instance.getRenderer(),
					m_center.x, m_center.y, m_size.x, m_size.y,
					m_color.r, m_color.g, m_color.b, m_color.a) != 0)
					throw std::runtime_error("PL : Can't draw a filled ellipse : " + std::string(SDL_GetError()));
			}

			else if (m_drawingType == pl::DrawingType::outlined)
			{
				if (aaellipseRGBA(
					m_instance.getRenderer(),
					m_center.x, m_center.y, m_size.x, m_size.y,
					m_color.r, m_color.g, m_color.b, m_color.a) != 0)
					throw std::runtime_error("PL : Can't draw an outlined ellipse : " + std::string(SDL_GetError()));
			}
		}

		pl::Block::render();
	}



} // namespace pl::block
