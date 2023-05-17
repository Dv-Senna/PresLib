#define SDL_MAIN_HANDLED

#include "pl/preslib.hpp"



int main(int argc, char *argv[])
{
	pl::Instance instance {};

	pl::Slide slide {};
	instance.addSlide(&slide);

	pl::block::Line line {instance, {10, 20}, {30, 40}};
	slide.addChildren(&line);

	pl::block::Line line2 {instance, {0, 0}, {0, PL_DEFAULT_VIEWPORT_HEIGHT}};
	pl::block::Line line3 {instance, {PL_DEFAULT_VIEWPORT_WIDTH - 1, 0}, {PL_DEFAULT_VIEWPORT_WIDTH - 1, PL_DEFAULT_VIEWPORT_HEIGHT}};
	slide.addChildren(&line2);
	slide.addChildren(&line3);


	instance.run();

	return 0;
}