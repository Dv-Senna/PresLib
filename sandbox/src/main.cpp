#include <iostream>
#include <exception>

#include <pl/preslib.hpp>

#include <pl/animations/distortion.hpp>
#include <pl/animations/motion.hpp>
#include <pl/animations/rotation.hpp>
#include <pl/animations/scaling.hpp>



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
		auto ellipse = instance.registerBlock(slide, {pl::Block::Type::ellipse, pl::blocks::Ellipse::CreateInfo(
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
			pl::utils::undefined,
			0.f, {0.5f, 0.5f},
			glm::scale(glm::mat4(1.f), {0.25f, 0.25f, 1.f})
		)});
		
		auto mathMotion = instance.registerAnimation(slide, {pl::Animation::Type::motion, 2.f,
			pl::Animation::InterpolationFunction::easeInOut,
			pl::Animation::StartFlag::onNext,
			pl::animations::EaseInOutMotion::CreateInfo(
				(pl::blocks::Math*)math.get(),
				{500, 1000},
				0.01f, 0.01f
			)
		});
		auto mathScaling = instance.registerAnimation(slide, {pl::Animation::Type::scaling, 2.f,
			pl::Animation::InterpolationFunction::linear,
			pl::Animation::StartFlag::withPrevious,
			pl::animations::LinearScaling::CreateInfo(
				(pl::blocks::Math*)math.get(),
				{1.25f, 0.825f}
			)
		});
		auto ellipseRotation = instance.registerAnimation(slide, {pl::Animation::Type::rotation, 7.f,
			pl::Animation::InterpolationFunction::easeInOut,
			pl::Animation::StartFlag::withPrevious,
			pl::animations::EaseInOutRotation::CreateInfo(
				(pl::blocks::Ellipse*)ellipse.get(),
				2.f * glm::pi<float> () * 5.f + 0.9f,
				0.001f, 0.001f
			)
		});




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
			pl::utils::undefined
		)});

		auto triangleMotion = instance.registerAnimation(slide2, {pl::Animation::Type::motion, 1.5f,
			pl::Animation::InterpolationFunction::easeIn,
			pl::Animation::StartFlag::withPrevious,
			pl::animations::EaseInMotion::CreateInfo(
				(pl::blocks::Triangle*)triangle.get(),
				{600.f, 300.f}
			)
		});
		auto textMotion = instance.registerAnimation(slide2, {pl::Animation::Type::motion, 0.5f,
			pl::Animation::InterpolationFunction::easeOut,
			pl::Animation::StartFlag::onNext,
			pl::animations::EaseOutMotion::CreateInfo(
				(pl::blocks::Text*)text.get(),
				{1500.f, 700.f},
				0.05f
			)
		});
		auto imageDistortion = instance.registerAnimation(slide2, {pl::Animation::Type::distortion, 0.5f,
			pl::Animation::InterpolationFunction::easeInOut,
			pl::Animation::StartFlag::onNext,
			pl::animations::EaseInOutDistortion::CreateInfo(
				(pl::blocks::Image*)image.get(),
				glm::mat4(
					1.f, 0.f, 0.f, 2.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f
				)
			)
		});

		


		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}