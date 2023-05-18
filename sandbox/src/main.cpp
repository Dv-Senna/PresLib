#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int argc, char *argv[])
{
	pl::Instance instance {};

	pl::Slide slide {};
	instance.addSlide(&slide);

	pl::block::Group background {instance};
	slide.addChildren(&background);

	pl::block::Rectangle rectangle {instance, {0, 0, PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT}, {30, 30, 30}};
	background.addChildren(&rectangle);

	pl::block::Line line {instance, {10, 20}, {30, 40}};
	slide.addChildren(&line);


	instance.run();

	return 0;
}