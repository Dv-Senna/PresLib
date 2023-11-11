#include <glm/gtc/matrix_transform.hpp>

#include "blocks/line.hpp"
#include "blocks/rectangle.hpp"
#include "instance.hpp"



namespace pl::blocks
{
	Line::Line(pl::Instance &instance, const pl::blocks::Line::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize({createInfo.length, createInfo.thickness}),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion)
	{
		pl::blocks::Rectangle::s_load(instance);

		if (m_color == pl::utils::undefined)
			m_color = m_instance.getStyle().colors.shape;
	}



	Line::~Line()
	{

	}



	void Line::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x * m_size.x, m_rotationCenter.y * m_size.y, 0.f};
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::translate(transformation, rotationCenter);
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::translate(transformation, -rotationCenter);
		transformation = glm::scale(transformation, {m_size.x, m_size.y, 1.f});

		m_instance.getRenderer().usePipeline(pl::blocks::Rectangle::s_pipeline);
			m_instance.getRenderer().setUniformValues(pl::blocks::Rectangle::s_pipeline, "vertices", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			m_instance.getRenderer().drawVertices(pl::blocks::Rectangle::s_vertices);
		m_instance.getRenderer().usePipeline(0);
	}



} // namespace pl::blocks
