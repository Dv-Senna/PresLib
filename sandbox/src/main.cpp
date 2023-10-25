#include <iostream>
#include <exception>

#include <pl/instance.hpp>


int main(int, char *[])
{
	try
	{
		pl::Instance::CreateInfo instanceCreateInfo {};
		instanceCreateInfo.graphicsApi = pl::GraphicsApi::OpenGL;
		pl::Instance instance {instanceCreateInfo};

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}