#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"
#include "pl/math/mat2.hpp"



int main(int argc, char *argv[])
{
	try
	{
		pl::math::Mat2 matrix {1, 2, 3, 4};
		std::cout << "Matrix : " << matrix << std::endl;

		matrix *= 3;
		std::cout << "Matrix : " << matrix << std::endl;

		matrix += matrix;
		std::cout << "Matrix : " << matrix << std::endl;
		std::cout << "Det : " << pl::math::det(matrix) << std::endl;
		std::cout << "Inverse : " << pl::math::inverse(matrix) << std::endl;

		matrix *= matrix;
		std::cout << "Matrix : " << matrix << std::endl;
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}