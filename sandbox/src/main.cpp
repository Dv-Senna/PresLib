#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_gpu> instance {};
		pl::Slide slide {instance};
		pl::Slide slide2 {instance};

		pl::blocks::Line line {instance, {10, 20}, {30, 40}, pl::utils::red};
		slide.addBlock(&line);

		pl::blocks::Rectangle rectFill {instance, {100, 100}, {100, 50}};
		slide.addBlock(&rectFill);
		pl::blocks::Rectangle rectBorder {instance, {200, 300}, {298, 72}, pl::utils::green, pl::RenderMethod::border};
		slide.addBlock(&rectBorder);

		pl::blocks::Triangle triFill {instance, {400, 400}, {450, 450}, {400, 450}, {255, 120, 0}};
		slide2.addBlock(&triFill);
		pl::blocks::Triangle triBorder {instance, {300, 300}, {320, 350}, {350, 310}, pl::utils::blue, pl::RenderMethod::border};
		slide2.addBlock(&triBorder);



		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}