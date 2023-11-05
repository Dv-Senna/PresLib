#include <glm/ext/matrix_transform.hpp>

#include "blocks/triangle.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/shader.hpp"
#include "graphics/vertices.hpp"
#include "instance.hpp"



namespace pl::blocks
{
	pl::utils::Id Triangle::s_shaders[2] {0, 0}, Triangle::s_pipeline {0};



	Triangle::Triangle(pl::Instance &instance, const pl::blocks::Triangle::CreateInfo &createInfo) :
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithOrientation(createInfo.angle),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion),
		m_vertices {0}
	{
		pl::blocks::Triangle::s_load(m_instance);

		glm::vec2 first {createInfo.a}, second {createInfo.b};

		pl::graphics::Vertices vertices {
			{
				0.f, 0.f,
				first.x, first.y,
				second.x, second.y
			},
			{
				{
					{pl::graphics::VerticesChannel::color, {0, 2, 0}}
				},
				pl::graphics::VerticesUsage::staticDraw
			}
		};
		m_vertices = m_instance.getRenderer().registerObject(pl::utils::ObjectType::vertices, vertices);
	}


	
	Triangle::~Triangle()
	{
		
	}



	void Triangle::draw(const glm::mat4 &globalTransformation)
	{
		glm::mat4 transformation {
			glm::rotate(
				glm::translate(glm::mat4(1.f), glm::vec3(m_position.x, m_position.y, 0.f)),
				static_cast<float> (m_angle), glm::vec3(0.f, 0.f, 1.f)
			)
		};

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "vertices", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			m_instance.getRenderer().drawVertices(m_vertices);
		m_instance.getRenderer().usePipeline(0);
	}



	void Triangle::s_load(pl::Instance &instance)
	{
		static bool loaded {false};
		if (loaded)
			return;

		loaded = true;

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
