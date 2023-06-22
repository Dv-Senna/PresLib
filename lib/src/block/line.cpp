#include <cmath>
#include <iostream>

#include "block/line.hpp"
#include "math/transform.hpp"



namespace pl::block
{
	Line::Line(
		pl::Instance &instance,
		pl::math::Vec2 start,
		pl::math::Vec2 end,
		const pl::utils::Color color
	) : 
		pl::Block(instance),
		m_start {start},
		m_color {color},
		m_transform {pl::math::identity2}
	{
		if (m_color.undefined)
			m_color = m_instance.getColors().getScheme().object;

		std::cout << "Line's color : " << m_color << std::endl;

		float angle {atan2(end.y - m_start.y, end.x - m_start.x)};
		float length = (end - m_start).length();

		m_transform = length * pl::math::rotate(m_transform, angle);

		std::cout << "Line : " << m_start << ", " << m_transform * pl::math::Vec2(1, 0) + m_start << std::endl;

		m_start = m_instance.getTransform() * m_start - pl::math::Vec2(0.5f, -0.5f);

		std::cout << "Line's start : " << m_start << std::endl;
	}



	void Line::render()
	{
		m_instance.getTransform() = m_instance.getTransform() * m_transform;
		m_instance.getShaders().use("line");
		m_instance.sendTransform();

		m_instance.getShaders().getCurrent().sendData("upos", m_start);
		m_instance.getShaders().getCurrent().sendData("ucolor", m_color);

		m_instance.getVertices().get("line").draw();

		m_instance.resetTransform();
	}



} // namespace pl::block
