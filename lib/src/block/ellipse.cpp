#include <cassert>
#include <stdexcept>

#include "block/ellipse.hpp"



namespace pl::block
{
	std::array<float, 12> Ellipse::s_vertices {
		0, 0,   0, 1,   1, 0,
		1, 1,   1, 0,   0, 1
	};


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
		m_drawingType {drawingType},
		m_flipWidthAndheight {false}
	{
		assert(m_excentricity < 1.0f && "PL : excentricity must be less than 1.0f");
		assert(m_excentricity >= 0.0f && "PL : excentricity must be positive");

		if (m_excentricity != 0)
		{
			m_size.x = m_size.x / m_excentricity;
			m_size.y = m_size.y * m_size.y * (1 / (m_excentricity * m_excentricity) - 1);
		}

		if (m_color.undefined)
			m_color = m_instance.getColors().getScheme().object;
	}



	void Ellipse::flipWidthAndHeight(bool flip)
	{
		m_flipWidthAndheight = flip;
	}



	void Ellipse::render()
	{
		if (m_excentricity == 0.0f)
		{
			if (m_drawingType == pl::DrawingType::filled)
			{
				m_instance.getShaders().getShader("circle").use();
			}

			else if (m_drawingType == pl::DrawingType::outlined)
			{
				
			}
		}

		else
		{
			if (m_drawingType == pl::DrawingType::filled)
			{
				
			}

			else if (m_drawingType == pl::DrawingType::outlined)
			{
				
			}
		}

		pl::Block::render();
	}



} // namespace pl::block
