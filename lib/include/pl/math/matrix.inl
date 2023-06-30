#include <type_traits>

#include "matrix.hpp"



namespace pl::math
{
	template <class T, size_t R, size_t C>
	Matrix<T, R, C>::Matrix() : m_datas {}
	{
		static_assert(std::is_arithmetic_v<T>, "PL : Matrix<T, R, C> type must be arithmetic");
		static_assert(R > 0, "PL : Matrix<T, R, C> must have a number of row positive");
		static_assert(C > 0, "PL : Matrix<T, R, C> must have a number of column positive");
	}



	template <class T, size_t R, size_t C>
	Matrix<T, R, C>::Matrix(T value) : Matrix<T, R, C> ()
	{
		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				m_datas[x][y] = value;
		}
	}



	template <class T, size_t R, size_t C>
	template <class ...Args>
	Matrix<T, R, C>::Matrix(T first, Args ...args) : Matrix<T, R, C> ()
	{
		size_t x {0}, y {1};
		m_datas[0][0] = first;

		for (const auto argument : {args...})
		{
			m_datas[x][y] = argument;

			y++;

			if (y % C != y)
			{
				y %= C;
				x++;
			}

			if (x >= R || y >= C)
				break;
		}
	}



	template <class T, size_t R, size_t C>
	Matrix<T, R, C>::Matrix(const pl::math::Matrix<T, R, C> &matrix) : Matrix<T, R, C> ()
	{
		m_datas = matrix.m_datas;
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator=(const pl::math::Matrix<T, R, C> &matrix)
	{
		m_datas = matrix.m_datas;
		return *this;
	}



	template <class T, size_t R, size_t C>
	Matrix<T, R, C>::Matrix(pl::math::Matrix<T, R, C> &&matrix) noexcept : Matrix<T, R, C> ()
	{
		m_datas = std::move(matrix.m_datas);
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator=(pl::math::Matrix<T, R, C> &&matrix) noexcept
	{
		m_datas = std::move(matrix.m_datas);
		return *this;
	}



	template <class T, size_t R, size_t C>
	std::array<T, C> &Matrix<T, R, C>::operator[](size_t row)
	{
		return m_datas[row];
	}



	template <class T, size_t R, size_t C>
	const std::array<T, C> &Matrix<T, R, C>::operator[](size_t row) const noexcept
	{
		return m_datas[row];
	}



	template <class T, size_t R, size_t C>
	inline std::array<std::array<T, C>, R> &Matrix<T, R, C>::get() noexcept
	{
		return m_datas;
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator+=(const pl::math::Matrix<T, R, C> &matrix)
	{
		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				m_datas[x][y] += matrix.m_datas[x][y];
		}

		return *this;
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator-=(const pl::math::Matrix<T, R, C> &matrix)
	{
		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				m_datas[x][y] -= matrix.m_datas[x][y];
		}

		return *this;
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator*=(T value)
	{
		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				m_datas[x][y] *= value;
		}

		return *this;
	}



	template <class T, size_t R, size_t C>
	const pl::math::Matrix<T, R, C> &Matrix<T, R, C>::operator/=(T value)
	{
		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				m_datas[x][y] /= value;
		}

		return *this;
	}



	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator+(pl::math::Matrix<T, R, C> a, const pl::math::Matrix<T, R, C> &b)
	{
		a += b;
		return a;
	}



	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator-(pl::math::Matrix<T, R, C> a, const pl::math::Matrix<T, R, C> &b)
	{
		a -= b;
		return a;
	}



	template <class T, size_t R, size_t N, size_t C>
	pl::math::Matrix<T, R, C> operator*(const pl::math::Matrix<T, R, N> &a, const pl::math::Matrix<T, N, C> &b)
	{
		pl::math::Matrix<T, R, C> result {static_cast<T> (0)};

		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
			{
				for (size_t n {0}; n < N; n++)
					result[x][y] += a[x][n] * b[n][y];
			}
		}
		
		return result;
	}



	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator*(pl::math::Matrix<T, R, C> a, T value)
	{
		a *= value;
		return a;
	}



	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator/(pl::math::Matrix<T, R, C> a, T value)
	{
		a /= value;
		return value;
	}



	template <class T, size_t R, size_t C>
	std::ostream &operator<<(std::ostream &stream, const pl::math::Matrix<T, R, C> &a)
	{
		stream << "[";

		for (size_t x {0}; x < R; x++)
		{
			stream << "(";

			for (size_t y {0}; y < C; y++)
			{
				stream << a[x][y];

				if (y != C - 1)
					stream << ", ";
			}

			stream << ")";

			if (x != R - 1)
				stream << ", ";
		}

		stream << "]";

		return stream;
	}



	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, C, R> transpose(const pl::math::Matrix<T, R, C> &matrix)
	{
		pl::math::Matrix<T, C, R> result {};

		for (size_t x {0}; x < R; x++)
		{
			for (size_t y {0}; y < C; y++)
				result[y][x] = matrix[x][y];
		}

		return result;
	}



} // namespace pl::math
