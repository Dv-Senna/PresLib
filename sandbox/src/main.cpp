#include <iostream>
#include <exception>

#include <pl/instance.hpp>


int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_renderer> instance {"PresLib"};


		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}