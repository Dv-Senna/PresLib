#include <iostream>
#include <exception>

#include <pl/blocks/ellipse.hpp>
#include <pl/blocks/group.hpp>
#include <pl/blocks/math.hpp>
#include <pl/blocks/rectangle.hpp>
#include <pl/blocks/triangle.hpp>
#include <pl/instance.hpp>
#include <pl/graphics/vertices.hpp>
#include <pl/graphics/shader.hpp>
#include <pl/graphics/pipeline.hpp>
#include <pl/graphics/texture.hpp>
#include <pl/utils/loadImage.hpp>




int main(int, char *[])
{
	try
	{
		pl::Instance::CreateInfo instanceCreateInfo {};
		instanceCreateInfo.viewportSize = {2560, 1440};
		instanceCreateInfo.graphicsApi = pl::graphics::Api::OpenGL;
		pl::Instance instance {instanceCreateInfo};


		auto slide = instance.registerSlide();
		auto group = instance.registerBlock(slide, {pl::Block::Type::group, pl::blocks::Group::CreateInfo(
			{0.f, 0.f},
			{1.f, 1.f},
			0.1f
		)});
		auto rectangle = instance.registerBlock(group, {pl::Block::Type::rectangle, pl::blocks::Rectangle::CreateInfo(
			{800, 200},
			{600, 300},
			pl::utils::yellow
		)});
		auto rectangle2 = instance.registerBlock(group, {pl::Block::Type::rectangle, pl::blocks::Rectangle::CreateInfo(
			{1300, 600},
			{600, 300},
			pl::utils::red,
			3.14159f / 2.f
		)});
		auto circle = instance.registerBlock(slide, {pl::Block::Type::ellipse, pl::blocks::Ellipse::CreateInfo(
			{2000, 500},
			{500, 1000},
			pl::utils::green
		)});
		auto math = instance.registerBlock(slide, {pl::Block::Type::math, pl::blocks::Math::CreateInfo(
			R"(R_{\mu\nu} - \dfrac{1}{2}Rg_{\mu\nu} + \Lambda g_{\mu\nu} + \dfrac{1}{2}\int R\nabla g_{\mu\nu} = \dfrac{8\pi G}{c^4} T_{\mu\nu})",
			20,
			{1000, 500},
			pl::utils::black
		)});

		auto slide2 = instance.registerSlide();
		auto triangle = instance.registerBlock(slide2, {pl::Block::Type::triangle, pl::blocks::Triangle::CreateInfo(
			{500.f, 0.f}, {600.f, 600.f},
			{400.f, 700.f},
			pl::utils::green
		)});
		auto line = instance.registerBlock(slide2, {pl::Block::Type::line, pl::blocks::Line::CreateInfo(
			{900.f, 200.f},
			600.f,
			5.f,
			pl::utils::orange
		)});


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

		pl::graphics::Uniform uniformInfos {
			{
				{pl::graphics::UniformFieldType::floating, "r"},
				{pl::graphics::UniformFieldType::floating, "g"},
				{pl::graphics::UniformFieldType::floating, "b"},
				{pl::graphics::UniformFieldType::mat4, "scale"}
			},
			"uni_Color",
			0
		};

		pl::graphics::Pipeline pipelineInfos {
			{vertexShader, fragmentShader},
			{uniformInfos}
		};
		auto pipeline = instance.getRenderer().registerObject(
			pl::utils::ObjectType::pipeline,
			pipelineInfos
		);

		instance.getRenderer().setUniformValues(pipeline, "uni_Color", {
			{"r", 1.f},
			{"g", 0.5f},
			{"b", 0.1f},
			{"scale", instance.getTransformation()}
		});


		glm::vec2 size {};
		auto texture = pl::utils::loadImage(instance, "logo.png", size);

		pl::graphics::Vertices verticesInfos {
			{
				0.f, 0.f,      0.f, 0.f,
				size.x / 4.f, size.y / 4.f,  1.f, 1.f,
				0.f, size.y / 4.f,    0.f, 1.f,

				0.f, 0.f,      0.f, 0.f,
				size.x / 4.f, 0.f,    1.f, 0.f,
				size.x / 4.f, size.y / 4.f,  1.f, 1.f,
			},
			{{
					{pl::graphics::VerticesChannel::position, {0, 2}},
					{pl::graphics::VerticesChannel::textureCoord0, {1, 2, 2}},
				},
				pl::graphics::VerticesUsage::staticDraw
			}
		};
		auto vertices = instance.getRenderer().registerObject(
			pl::utils::ObjectType::vertices,
			verticesInfos
		);


		instance.setRenderingCallback([&]() {
			instance.getRenderer().setUniformValues(pipeline, "uni_Color", {
				{"scale", instance.getTransformation()}
			});

			instance.getRenderer().usePipeline(pipeline);
				instance.getRenderer().bindTexture(pipeline, texture, 0);
					instance.getRenderer().drawVertices(vertices);
				instance.getRenderer().bindTexture(pipeline, 0, 0);
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