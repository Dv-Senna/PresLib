#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"
#include "pl/themes/modern.hpp"



int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_renderer> instance {};
		pl::themes::Modern modern {instance};
		instance.getFonts().add("arial", "arial.ttf");


		pl::Slide slide {instance};
		pl::blocks::Title slideTitle {instance, "An amazing title", slide};
		pl::Slide slide2 {instance, pl::SlideFlag::noBackground};
		pl::blocks::Title slideTitle2 {instance, "The new style | modern", slide2};

		pl::blocks::Line line {instance, {10, 20}, {30, 40}, pl::utils::red};
		slide.addBlock(&line);

		pl::blocks::Rectangle rectFill {instance, {100, 100}, {100, 50}};
		slide.addBlock(&rectFill);
		pl::blocks::Rectangle rectBorder {instance, {200, 300}, {298, 72}, pl::utils::green, pl::RenderMethod::border};
		slide.addBlock(&rectBorder);

		pl::blocks::Ellipse circleFill {instance, {200, 200}, 50.0f};
		slide.addBlock(&circleFill);
		pl::blocks::Ellipse circleBorder {
			instance, {300, 200}, 50.0f,
			pl::args::color(pl::utils::white), pl::args::drawingMethod(pl::RenderMethod::border), pl::args::borderThickness(10.f)};
		slide.addBlock(&circleBorder);

		pl::blocks::Ellipse ellipseFill {instance, {400, 200}, 50.0f, pl::args::excentricity(0.5f)};
		slide.addBlock(&ellipseFill);
		pl::blocks::Ellipse ellipseBorder {
			instance, {600, 200}, 50.0f,
			pl::args::excentricity(0.5f), pl::args::angle(45.0f), pl::args::color(pl::utils::white), pl::args::drawingMethod(pl::RenderMethod::border)};
		slide.addBlock(&ellipseBorder);


		pl::blocks::Triangle triFill {instance, {400, 400}, {450, 450}, {400, 450}, {255, 120, 0}};
		slide2.addBlock(&triFill);
		pl::blocks::Triangle triBorder {instance, {300, 300}, {320, 350}, {350, 310}, pl::utils::blue, pl::RenderMethod::border};
		slide2.addBlock(&triBorder);

		pl::blocks::Image image {instance, "image.png", {100, 100}};
		slide2.addBlock(&image);

		pl::blocks::Text text {instance, "Hello World from PresLib !", {600, 500}, "arial", 30};
		slide2.addBlock(&text);

		pl::blocks::Math math {instance, "E = mc^2", {0, 300}, 15};
		slide2.addBlock(&math);


		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}