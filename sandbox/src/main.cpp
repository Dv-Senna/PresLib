#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"



int main(int, char *[])
{
	try
	{
		pl::math::Vec2<float> vec {1.0f, 2.0f};

		std::cout << vec << std::endl;

		vec += {2.f, 3.f};
		std::cout << vec << std::endl;

		vec -= {1.f, 2.f};
		std::cout << vec << std::endl;

		std::cout << pl::math::length(vec) << std::endl;

		pl::Instance<pl::GraphicsApi::SDL2_renderer> instance {};
		pl::Slide slide {instance};

		pl::blocks::Line line {instance, 10, 20, 30, 40};
		slide.addBlock(&line);

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}