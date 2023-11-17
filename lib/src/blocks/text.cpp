#include <iostream>

#include <glm/ext/matrix_transform.hpp>

#include "blocks/text.hpp"
#include "instance.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/shader.hpp"
#include "graphics/text.hpp"
#include "graphics/vertices.hpp"
#include "utils/output.hpp"



namespace pl::blocks
{
	pl::utils::Id Text::s_shaders[2] {0, 0}, Text::s_pipeline {0};



	Text::Text(pl::Instance &instance, const pl::blocks::Text::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion),
		m_vertices {},
		m_textures {}
	{
		pl::blocks::Text::s_load(m_instance);

		m_vertices = pl::graphics::generateVerticesFromText(m_instance, createInfo.font, createInfo.fontSize, createInfo.text, m_textures);
	}



	Text::~Text()
	{

	}



	void Text::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x, m_rotationCenter.y, 0.f};
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::translate(transformation, rotationCenter);
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::translate(transformation, -rotationCenter);

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "text", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			for (size_t i {0}; i < std::min(m_vertices.size(), m_textures.size()); ++i)
			{
				m_instance.getRenderer().bindTexture(s_pipeline, m_textures[i], 0);
				m_instance.getRenderer().drawVertices(m_vertices[i]);
			}
			m_instance.getRenderer().bindTexture(s_pipeline, 0, 0);
		m_instance.getRenderer().usePipeline(0);
	}



	void Text::s_load(pl::Instance &instance)
	{
		static bool loaded {false};
		if (loaded)
			return;

		loaded = true;

		pl::graphics::Shader vertexShader {
			pl::graphics::ShaderType::vertex,
			"shaders/text.vert.spv",
			"main"
		};
		s_shaders[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, vertexShader);
		pl::graphics::Shader fragmentShader {
			pl::graphics::ShaderType::fragment,
			"shaders/text.frag.spv",
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
				"text", 0
			}},
			{{
				{pl::graphics::VerticesChannel::position, {0, 2}},
				{pl::graphics::VerticesChannel::textureCoord0, {1, 2, 2}}
			}}
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);
	}



} // namespace pl::blocks
