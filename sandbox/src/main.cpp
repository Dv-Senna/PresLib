#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_renderer> instance {};

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}