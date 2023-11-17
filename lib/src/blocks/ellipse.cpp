#include <glm/gtc/matrix_transform.hpp>

#include "blocks/ellipse.hpp"
#include "instance.hpp"
#include "graphics/vertices.hpp"
#include "graphics/shader.hpp"
#include "graphics/pipeline.hpp"



namespace pl::blocks
{
	pl::utils::Id Ellipse::s_vertices {0}, Ellipse::s_shaders[2] {0, 0}, Ellipse::s_pipeline {0};



	Ellipse::Ellipse(pl::Instance &instance, const pl::blocks::Ellipse::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize(createInfo.size),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion)
	{
		pl::blocks::Ellipse::s_load(m_instance);
	}



	Ellipse::~Ellipse()
	{

	}



	void Ellipse::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x * m_size.x, m_rotationCenter.y * m_size.y, 0.f};
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::translate(transformation, rotationCenter);
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::translate(transformation, -rotationCenter);
		transformation = glm::scale(transformation, {m_size.x, m_size.y, 1.f});

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "vertices", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)},
				{"fade", 0.01f * (m_size.x > m_size.y ? m_size.y / m_size.x : m_size.x / m_size.y)}
			});
			m_instance.getRenderer().drawVertices(s_vertices);
		m_instance.getRenderer().usePipeline(0);
	}



	void Ellipse::s_load(pl::Instance &instance)
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
			"shaders/ellipse.vert.spv",
			"main"
		};
		s_shaders[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, vertexShader);
		pl::graphics::Shader fragmentShader {
			pl::graphics::ShaderType::fragment,
			"shaders/ellipse.frag.spv",
			"main"
		};
		s_shaders[1] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, fragmentShader);

		pl::graphics::Pipeline pipeline {
			{s_shaders[0], s_shaders[1]},
			{{
				{
					{pl::graphics::UniformFieldType::mat4, "transformation"},
					{pl::graphics::UniformFieldType::vec4, "color"},
					{pl::graphics::UniformFieldType::floating, "fade"}
				},
				"vertices", 0
			}},
			vertices.format
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);
	}



} // namespace pl::blocks
