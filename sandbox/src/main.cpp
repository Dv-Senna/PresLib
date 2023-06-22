#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int argc, char *argv[])
{
	try
	{
		
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}