#define SDL_MAIN_HANDLED

#include "pl/preslib.hpp"



int main(int argc, char *argv[])
{
	pl::Instance instance {};

	instance.run();

	return 0;
}