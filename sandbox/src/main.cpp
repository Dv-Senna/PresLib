#include <iostream>
#include <exception>

#include <pl/instance.hpp>
#include <pl/graphics/vertices.hpp>
#include <pl/graphics/shader.hpp>
#include <pl/graphics/pipeline.hpp>


int main(int, char *[])
{
	try
	{
		pl::Instance::CreateInfo instanceCreateInfo {};
		instanceCreateInfo.graphicsApi = pl::graphics::Api::OpenGL;
		pl::Instance instance {instanceCreateInfo};


		pl::graphics::Vertices verticesInfos {
			{
				0.0f, 0.5f,     1.f, 0.f, 0.f,
				-0.5f, -0.5f,   0.f, 1.f, 0.f,
				0.5f, -0.5f,    0.f, 0.f, 1.f
			},
			{{
					{pl::graphics::VerticesChannel::position, {0, 2}},
					{pl::graphics::VerticesChannel::color, {1, 3, 2}},
				},
				pl::graphics::VerticesUsage::staticDraw
			}
		};
		auto vertices = instance.getRenderer().registerObject(
			pl::utils::ObjectType::vertices,
			verticesInfos
		);

		pl::graphics::Shader vertexShaderInfos {
			pl::graphics::ShaderType::vertex,
			"shaders/test.vert.spv",
			"main"
		};
		pl::graphics::Shader fragmentShaderInfos {
			pl::graphics::ShaderType::fragment,
			"shaders/test.frag.spv",
			"main"
		};

		auto vertexShader = instance.getRenderer().registerObject(
			pl::utils::ObjectType::shader,
			vertexShaderInfos
		);
		auto fragmentShader = instance.getRenderer().registerObject(
			pl::utils::ObjectType::shader,
			fragmentShaderInfos
		);

		pl::graphics::Pipeline pipelineInfos {
			{vertexShader, fragmentShader},
			{}
		};
		auto pipeline = instance.getRenderer().registerObject(
			pl::utils::ObjectType::pipeline,
			pipelineInfos
		);

		instance.setRenderingCallback([&]() {
			instance.getRenderer().usePipeline(pipeline);
				instance.getRenderer().drawVertices(vertices);
			instance.getRenderer().usePipeline(0);
		});

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}