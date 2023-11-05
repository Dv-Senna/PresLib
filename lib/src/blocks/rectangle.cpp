#include <iostream>

#include <glm/ext/matrix_transform.hpp>

#include "blocks/rectangle.hpp"
#include "instance.hpp"
#include "graphics/vertices.hpp"
#include "graphics/shader.hpp"
#include "graphics/pipeline.hpp"
#include "utils/output.hpp"
#include "utils/transformation.hpp"



namespace pl::blocks
{
	pl::utils::Id Rectangle::s_vertices {0}, Rectangle::s_shaders[2] {0, 0}, Rectangle::s_pipeline {0};



	Rectangle::Rectangle(pl::Instance &instance, const pl::blocks::Rectangle::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize(createInfo.size),
		pl::BlockWithOrientation(createInfo.angle),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion)
	{
		pl::blocks::Rectangle::s_load(m_instance);
	}



	Rectangle::~Rectangle()
	{

	}



	void Rectangle::draw(const glm::mat4 &globalTransformation)
	{
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::scale(transformation, {m_size.x, m_size.y, 1.f});

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "vertices", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			m_instance.getRenderer().drawVertices(s_vertices);
		m_instance.getRenderer().usePipeline(0);
	}



	void Rectangle::s_load(pl::Instance &instance)
	{
		static bool loaded {false};
		if (loaded)
			return;

		loaded = true;

		pl::graphics::Vertices vertices {
			{
				0.f, 0.f,    1.f, 1.f,    0.f, 1.f,
				0.f, 0.f,    1.f, 0.f,    1.f, 1.f
			},
			{
				{
					{pl::graphics::VerticesChannel::color, {0, 2, 0}}
				},
				pl::graphics::VerticesUsage::staticDraw
			}
		};
		s_vertices = instance.getRenderer().registerObject(pl::utils::ObjectType::vertices, vertices);

		pl::graphics::Shader vertexShader {
			pl::graphics::ShaderType::vertex,
			"shaders/vertices.vert.spv",
			"main"
		};
		s_shaders[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, vertexShader);
		pl::graphics::Shader fragmentShader {
			pl::graphics::ShaderType::fragment,
			"shaders/vertices.frag.spv",
			"main"
		};
		s_shaders[1] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, fragmentShader);

		pl::graphics::Pipeline pipeline {
			{s_shaders[0], s_shaders[1]},
			{{
				{
					{pl::graphics::UniformFieldType::mat4, "transformation"},
					{pl::graphics::UniformFieldType::vec4, "color"}
				},
				"vertices", 0
			}}
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);
	}



} // namespace pl::blocks
