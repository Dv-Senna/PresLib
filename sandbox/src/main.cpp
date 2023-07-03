#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_gpu> instance {};
		pl::Slide slide {instance};

		pl::blocks::Line line {instance, {10, 20}, {30, 40}, pl::utils::red};
		slide.addBlock(&line);

		pl::blocks::Rectangle rectFill {instance, {100, 100}, {100, 50}};
		slide.addBlock(&rectFill);
		pl::blocks::Rectangle rectBorder {instance, {200, 300}, {298, 72}, pl::utils::green, pl::RenderMethod::border};
		slide.addBlock(&rectBorder);

		pl::blocks::Triangle triFill {instance, {410, 410}, {420, 420}, {410, 420}};
		slide.addBlock(&triFill);
		pl::blocks::Triangle triBorder {instance, {310, 310}, {320, 320}, {320, 310}, pl::utils::blue, pl::RenderMethod::border};
		slide.addBlock(&triBorder);

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}