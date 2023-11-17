#include <iostream>
#include <sstream>

#include <glm/ext/matrix_transform.hpp>

#include "blocks/image.hpp"
#include "instance.hpp"
#include "graphics/vertices.hpp"
#include "graphics/shader.hpp"
#include "graphics/pipeline.hpp"
#include "utils/loadImage.hpp"
#include "utils/output.hpp"



namespace pl::blocks
{
	pl::utils::Id Image::s_vertices {0}, Image::s_shaders[2] {0, 0}, Image::s_pipeline {0};



	Image::Image(pl::Instance &instance, const pl::blocks::Image::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize({0.f, 0.f}),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion),
		m_texture {0}
	{
		pl::blocks::Image::s_load(m_instance);
		m_texture = pl::utils::loadImage(m_instance, createInfo.path, m_size);
	}



	Image::~Image()
	{

	}



	void Image::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x * m_size.x, m_rotationCenter.y * m_size.y, 0.f};
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::translate(transformation, rotationCenter);
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::translate(transformation, -rotationCenter);
		transformation = glm::scale(transformation, {m_size.x, m_size.y, 1.f});

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "texture", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			m_instance.getRenderer().bindTexture(s_pipeline, m_texture, 0);
				m_instance.getRenderer().drawVertices(s_vertices);
			m_instance.getRenderer().bindTexture(s_pipeline, 0, 0);
		m_instance.getRenderer().usePipeline(0);
	}



	void Image::s_load(pl::Instance &instance)
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
			"shaders/texture.vert.spv",
			"main"
		};
		s_shaders[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, vertexShader);
		pl::graphics::Shader fragmentShader {
			pl::graphics::ShaderType::fragment,
			"shaders/texture.frag.spv",
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
				"texture", 0
			}},
			vertices.format
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);
	}



} // namespace pl::blocks
