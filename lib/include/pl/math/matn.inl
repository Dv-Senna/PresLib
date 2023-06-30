#include "matn.hpp"



namespace pl::math
{
	template <class T, size_t N>
	Matn<T, N>::Matn() : pl::math::Matrix<T, N, N> ()
	{

	}



	template <class T, size_t N>
	Matn<T, N>::Matn(T value) : pl::math::Matrix<T, N, N> (value)
	{

	}



	template <class T, size_t N>
	template <class ...Args>
	Matn<T, N>::Matn(T first, Args ...args) : pl::math::Matrix<T, N, N> (first, args...)
	{

	}



	template <class T, size_t N>
	T det(const pl::math::Matn<T, N> &matrix)
	{
		static_assert(N < 5, "PL : The determinant function is implemented only for N = (1, 2, 3)");

		if constexpr (N == 1)
			return matrix[0][0];

		if constexpr (N == 2)
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

		if constexpr (N == 3)
		{
			return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
				- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2])
				+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
		}
	}



	template <class T, size_t N>
	pl::math::Matn<T, N> inverse(const pl::math::Matn<T, N> &matrix)
	{
		
	}



} // namespace pl::math
