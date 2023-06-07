#include "math/mat2.hpp"



namespace pl::math
{
	
	Mat2::Mat2(float a, float b, float c, float d) : m_data {a, b, c, d}
	{

	}



	Mat2::~Mat2()
	{

	}



	Mat2::Mat2(const pl::math::Mat2 &matrix) : m_data {matrix.m_data}
	{

	}



	const pl::math::Mat2 &Mat2::operator=(const pl::math::Mat2 &matrix)
	{
		m_data = matrix.m_data;
		return *this;
	}



	Mat2::Mat2(pl::math::Mat2 &&matrix) noexcept : m_data {std::move(matrix.m_data)}
	{

	}



	const pl::math::Mat2 &Mat2::operator=(pl::math::Mat2 &&matrix) noexcept
	{
		m_data = std::move(matrix.m_data);
		return *this;
	}



	pl::math::Mat2 &Mat2::operator+=(const pl::math::Mat2 &matrix)
	{
		for (int i = 0; i < 4; i++)
			m_data[i] += matrix.m_data[i];

		return *this;
	}



	pl::math::Mat2 &Mat2::operator-=(const pl::math::Mat2 &matrix)
	{
		for (int i = 0; i < 4; i++)
			m_data[i] -= matrix.m_data[i];

		return *this;
	}



	pl::math::Mat2 &Mat2::operator*=(const pl::math::Mat2 &matrix)
	{
		std::array<float, 4> tmp {};

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				tmp[i + j * 2] = 0;

				for (int p = 0; p < 2; p++)
					tmp[i + j * 2] += m_data[i + p * 2] * matrix.m_data[p + j * 2];
			}
		}

		m_data = tmp;

		return *this;
	}



	pl::math::Mat2 &Mat2::operator*=(float value)
	{
		for (int i = 0; i < 4; i++)
			m_data[i] *= value;

		return *this;
	}



	float det(const pl::math::Mat2 &matrix)
	{
		return matrix.get()[0] * matrix.get()[3] - matrix.get()[1] * matrix.get()[2];
	}



	pl::math::Mat2 inverse(const pl::math::Mat2 &matrix)
	{
		return (1 / det(matrix)) * pl::math::Mat2(matrix.get()[3], -matrix.get()[1], -matrix.get()[2], matrix.get()[0]);
	}




} // namespace pl::math

