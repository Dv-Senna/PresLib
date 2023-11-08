#include <iostream>
#include <exception>

#include <pl/blocks/group.hpp>
#include <pl/blocks/rectangle.hpp>
#include <pl/blocks/triangle.hpp>
#include <pl/instance.hpp>
#include <pl/graphics/vertices.hpp>
#include <pl/graphics/shader.hpp>
#include <pl/graphics/pipeline.hpp>
#include <pl/graphics/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


class PixelDeleter
{
	public:
		void operator() (unsigned char *pixels)
		{
			stbi_image_free(pixels);
			pixels = nullptr;
		}
};


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

		auto slide2 = instance.registerSlide();
		auto triangle = instance.registerBlock(slide2, {pl::Block::Type::triangle, pl::blocks::Triangle::CreateInfo(
			{500.f, 0.f}, {600.f, 600.f},
			{400.f, 700.f},
			pl::utils::green
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


		int channelCount {};
		int width {}, height {};
		stbi_set_flip_vertically_on_load(true);
		std::shared_ptr<unsigned char> pixels {
			stbi_load("logo.png", &width, &height, &channelCount, 0),
			PixelDeleter()
		};
		if (pixels == nullptr)
			throw std::runtime_error("Could not load image logo.png");

		pl::graphics::Texture textureInfos {
			{width, height},
			pixels,
			pl::graphics::ColorFormat::r8g8b8a8
		};
		auto texture = instance.getRenderer().registerObject(
			pl::utils::ObjectType::texture,
			textureInfos
		);


		pl::graphics::Vertices verticesInfos {
			{
				0.f, 0.f,      0.f, 0.f,
				width / 4.f, height / 4.f,  1.f, 1.f,
				0.f, height / 4.f,    0.f, 1.f,

				0.f, 0.f,      0.f, 0.f,
				width / 4.f, 0.f,    1.f, 0.f,
				width / 4.f, height / 4.f,  1.f, 1.f,
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