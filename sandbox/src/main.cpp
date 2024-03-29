#include <iostream>
#include <exception>

#include <pl/preslib.hpp>



int main(int, char *[])
{
	try
	{
		pl::Instance::CreateInfo instanceCreateInfo {};
		instanceCreateInfo.viewportSize = {2560, 1440};
		instanceCreateInfo.graphicsApi = pl::graphics::Api::OpenGL;
		pl::Instance instance {instanceCreateInfo};
		instance.getFont().registerFont("roboto", "fonts/roboto/Roboto-Regular.ttf");


		auto slide = instance.registerSlide();
		auto copyrightMark = instance.registerBlock(slide, {pl::Block::Type::text, pl::blocks::Text::CreateInfo(
			"© Dv-Senna 2023",
			30,
			"roboto",
			{2300, 50},
			{0, 0, 0, 150}
		)});
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
		auto image = instance.registerBlock(slide, {pl::Block::Type::image, pl::blocks::Image::CreateInfo(
			"logo.png",
			{0, 0},
			pl::utils::white,
			0.f, {0.5f, 0.5f},
			glm::scale(glm::mat4(1.f), {0.25f, 0.25f, 1.f})
		)});




		auto slide2 = instance.registerSlide();
		(void)instance.registerBlock(slide2, copyrightMark);
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
		(void)instance.registerBlock(slide2, image);
		auto text = instance.registerBlock(slide2, {pl::Block::Type::text, pl::blocks::Text::CreateInfo(
			"Hello World !",
			50,
			"roboto",
			{1000, 300},
			pl::utils::black
		)});


		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}