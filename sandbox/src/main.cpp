#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int argc, char *argv[])
{
	try
	{
		pl::Instance instance {};

		instance.getFonts().addFont("arial", "arial.ttf");



		pl::Slide slide {};
		instance.addSlide(&slide);

		pl::block::Group background {instance};
		slide.addChildren(&background);

		pl::block::Rectangle rectangle {instance, PL_ALL_VIEWPORT_RECT, {30, 30, 30}};
		background.addChildren(&rectangle);

		pl::block::Line line {instance, {10, 20}, {30, 40}};
		slide.addChildren(&line);

		pl::block::Ellipse circle {instance, {100, 100}, 30};
		slide.addChildren(&circle);


		pl::Slide slide2 {};
		instance.addSlide(&slide2);
		slide2.addChildren(&background);

		pl::block::Ellipse ellipse {instance, {400, 400}, 20, 0.9f};
		ellipse.flipWidthAndHeight();
		slide2.addChildren(&ellipse);

		pl::block::Text text {instance, {500, 500}, "Hello World from PresLib !", "arial", 30};
		slide2.addChildren(&text);

		pl::block::Image image {instance, "image.png", {384, 583}, 2.0f};
		slide2.addChildren(&image);

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}