#include <glm/gtc/matrix_transform.hpp>

#include "graphics/framebuffer.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/shader.hpp"
#include "graphics/vertices.hpp"
#include "instance.hpp"
#include "slide.hpp"



namespace pl
{
	pl::utils::Id Slide::s_vertices {}, Slide::s_shader[2] {}, Slide::s_pipeline {};
	glm::mat4 Slide::s_transformationMatrix {1.f};



	Slide::Slide(pl::Instance &instance, const pl::Slide::CreateInfo & /* createInfos */) : 
		m_instance {instance},
		m_blocks {},
		m_framebuffer {},
		m_framebufferTexture {}
	{
		pl::Slide::s_load(instance);

		pl::graphics::Framebuffer framebuffer {
			m_instance.getViewportSize(),
			pl::config::useMSAA ? pl::config::MSAASamplesCount : 0
		};
		m_framebuffer = m_instance.getRenderer().registerObject(pl::utils::ObjectType::framebuffer, framebuffer);
		m_framebufferTexture = m_instance.getRenderer().getFramebufferTexture(m_framebuffer);
	}



	void Slide::drawBlocks()
	{
		m_instance.getRenderer().useFramebuffer(m_framebuffer);
			m_instance.getRenderer().cleanViewport(m_instance.getStyle().colors.background);

			for (auto &block : m_blocks)
			{
				block->draw(s_transformationMatrix);
			}
		m_instance.getRenderer().useFramebuffer(0);
	}



	void Slide::draw(const glm::mat4 &globalTransformation)
	{
		m_instance.getRenderer().setUniformValues(s_pipeline, "uni_FramebufferTransformation", {
			{"uni_Transformation", globalTransformation}
		});

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().bindTexture(s_pipeline, m_framebufferTexture, 0);
				m_instance.getRenderer().drawVertices(s_vertices, true);
			m_instance.getRenderer().bindTexture(s_pipeline, 0, 0);
		m_instance.getRenderer().usePipeline(0);
	}



	void Slide::registerBlock(std::shared_ptr<pl::Block> block)
	{
		m_blocks.push_back(block);
	}



	void Slide::s_load(pl::Instance &instance)
	{
		bool loaded {false};
		if (loaded)
			return;

		loaded = true;

		pl::graphics::Vertices vertices {
			{
				1.f, 1.f,      1.f, 1.f,
				-1.f, -1.f,    0.f, 0.f,
				1.f, -1.f,     1.f, 0.f,

				-1.f, 1.f,     0.f, 1.f,
				-1.f, -1.f,    0.f, 0.f,
				1.f, 1.f,      1.f, 1.f
			},
			{{
				{pl::graphics::VerticesChannel::position, {0, 2}},
				{pl::graphics::VerticesChannel::textureCoord0, {1, 2, 2}}
			}}
		};
		s_vertices = instance.getRenderer().registerObject(pl::utils::ObjectType::vertices, vertices);


		pl::graphics::Shader shaders[2] {
			{
				pl::graphics::ShaderType::vertex,
				"shaders/framebuffer.vert.spv",
				"main"
			},
			{
				pl::graphics::ShaderType::fragment,
				pl::config::useMSAA ? "shaders/framebufferMSAA.frag.spv" : "shaders/framebuffer.frag.spv",
				"main"
			}
		};
		s_shader[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, shaders[0]);
		s_shader[1] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, shaders[1]);

		pl::graphics::Uniform fragmentUniforms {
			{
				{pl::graphics::UniformFieldType::floating, "uni_SamplesCount"},
				{pl::graphics::UniformFieldType::vec2, "uni_ViewportSize"}
			},
			"uni_WindowFramebufferBlock",
			0
		};
		pl::graphics::Uniform vertexUniforms {
			{
				{pl::graphics::UniformFieldType::mat4, "uni_Transformation"}
			},
			"uni_FramebufferTransformation",
			1
		};

		pl::graphics::Pipeline pipeline {
			{s_shader[0], s_shader[1]},
			pl::config::useMSAA ? std::vector<pl::graphics::Uniform> ({fragmentUniforms, vertexUniforms}) : std::vector<pl::graphics::Uniform> ({vertexUniforms})
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);

		if (pl::config::useMSAA)
		{
			instance.getRenderer().setUniformValues(s_pipeline, "uni_WindowFramebufferBlock", {
				{"uni_SamplesCount", static_cast<float> (pl::config::MSAASamplesCount)},
				{"uni_ViewportSize", instance.getViewportSize()}
			});
		}

		
		s_transformationMatrix = glm::ortho(0.f, instance.getWindowSize().x, 0.f, instance.getWindowSize().y);
	}



} // namespace pl
