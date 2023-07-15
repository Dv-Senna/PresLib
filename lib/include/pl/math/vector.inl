#include <cmath>
#include <type_traits>

#include "vector.hpp"



namespace pl::math
{
	template <class T, size_t D>
	Vector<T, D>::Vector() : m_datas {}
	{
		static_assert(D > 0, "PL : the size of pl::math::Vector<T, D> must be positive and non-null");
		static_assert(std::is_arithmetic_v<T>, "PL : the type given to pl::math::Vector<T, D> must be an arithmetic type");
	}



	template <class T, size_t D>
	Vector<T, D>::Vector(T value) : Vector<T, D> ()
	{
		for (T &data : m_datas)
			data = value;
	}



	template <class T, size_t D>
	template <class ...Args>
	Vector<T, D>::Vector(T first, Args ...args) : Vector<T, D> ()
	{
		m_datas = std::array<T, D> ({first, args...});
	}



	template <class T, size_t D>
	Vector<T, D>::Vector(const pl::math::Vector<T, D> &vec) : Vector<T, D> ()
	{
		m_datas = vec.m_datas;
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator=(const pl::math::Vector<T, D> &vec)
	{
		m_datas = vec.m_datas;
		return *this;
	}



	template <class T, size_t D>
	Vector<T, D>::Vector(pl::math::Vector<T, D> &&vec) noexcept : Vector<T, D> ()
	{
		m_datas = std::move(vec.m_datas);
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator=(pl::math::Vector<T, D> &&vec) noexcept
	{
		m_datas = std::move(vec.m_datas);
		return *this;
	}



	template <class T, size_t D>
	T &Vector<T, D>::operator[](size_t index)
	{
		return m_datas[index];
	}



	template <class T, size_t D>
	const T &Vector<T, D>::operator[](size_t index) const noexcept
	{
		return m_datas[index];
	}



	template <class T, size_t D>
	std::array<T, D> &Vector<T, D>::get() noexcept
	{
		return m_datas;
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator+=(const pl::math::Vector<T, D> &b)
	{
		for (size_t i {0}; i < D; i++)
			this->m_datas[i] += b.m_datas[i];

		return *this;
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator-=(const pl::math::Vector<T, D> &b)
	{
		for (size_t i {0}; i < D; i++)
			this->m_datas[i] -= b.m_datas[i];

		return *this;
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator*=(T value)
	{
		for (size_t i {0}; i < D; i++)
			m_datas[i] *= value;

		return *this;
	}



	template <class T, size_t D>
	const pl::math::Vector<T, D> &Vector<T, D>::operator/=(T value)
	{
		for (size_t i {0}; i < D; i++)
			m_datas[i] /= value;

		return *this;
	}



	template <class T, size_t D>
	bool Vector<T, D>::operator==(const pl::math::Vector<T, D> &vector) const noexcept
	{
		for (size_t i {0}; i < D; i++)
		{
			if (m_datas[i] != vector[i])
				return false;
		}

		return true;
	}



	template <class T, size_t D>
	pl::math::Vector<T, D> operator+(pl::math::Vector<T, D> a, const pl::math::Vector<T, D> &b)
	{
		a += b;
		return a;
	}



	template <class T, size_t D>
	pl::math::Vector<T, D> operator-(pl::math::Vector<T, D> a, const pl::math::Vector<T, D> &b)
	{
		a -= b;
		return a;
	}



	template <class T, size_t D>
	pl::math::Vector<T, D> operator*(pl::math::Vector<T, D> vector, T value)
	{
		vector *= value;
		return vector;
	}



	template <class T, size_t D>
	pl::math::Vector<T, D> operator/(pl::math::Vector<T, D> vector, T value)
	{
		vector /= value;
		return vector;
	}



	template <class T, size_t D>
	T operator*(const pl::math::Vector<T, D> &a, const pl::math::Vector<T, D> &b)
	{
		T result {0};

		for (size_t i {0}; i < D; i++)
			result += a[i] * b[i];

		return result;
	}



	template <class T, size_t D>
	std::ostream &operator<<(std::ostream &stream, const pl::math::Vector<T, D> &vector)
	{
		stream << "(";

		for (size_t i {0}; i < D; i++)
		{
			stream << vector[i];

			if (i != D - 1)
				stream << ", ";
		}

		stream << ")";

		return stream;
	}



	template <class T, size_t D>
	T dot(const pl::math::Vector<T, D> &a, const pl::math::Vector<T, D> &b)
	{
		return a * b;
	}



	template <class T, size_t D>
	T length(const pl::math::Vector<T, D> &vector)
	{
		T length {0};

		for (size_t i {0}; i < D; i++)
			length += vector[i] * vector[i];

		return sqrt(length);
	}



	template <class T, size_t D>
	T unit(const pl::math::Vector<T, D> &vector)
	{
		return vector / pl::math::length(vector);
	}



} // namespace pl::math
