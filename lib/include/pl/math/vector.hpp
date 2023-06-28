#pragma once

#include <array>
#include <cinttypes>
#include <ostream>


namespace pl::math
{
	template <class T, size_t D>
	class Vector
	{
		public:
			Vector();
			Vector(T value);
			template <class ...Args>
			Vector(T first, Args ...args);
			~Vector() = default;

			Vector(const pl::math::Vector<T, D> &vec);
			const pl::math::Vector<T, D> &operator=(const pl::math::Vector<T, D> &vec);

			Vector(pl::math::Vector<T, D> &&vec) noexcept;
			const pl::math::Vector<T, D> &operator=(pl::math::Vector<T, D> &&vec) noexcept;

			T &operator[](size_t index);
			const T &operator[](size_t index) const noexcept;

			std::array<T, D> &get() noexcept;

			const pl::math::Vector<T, D> &operator+=(const pl::math::Vector<T, D> &b);
			const pl::math::Vector<T, D> &operator-=(const pl::math::Vector<T, D> &b);

			const pl::math::Vector<T, D> &operator*=(T value);
			const pl::math::Vector<T, D> &operator/=(T value);


		protected:
			std::array<T, D> m_datas;
	};


	template <class T, size_t D>
	inline pl::math::Vector<T, D> operator+(pl::math::Vector<T, D> a, const pl::math::Vector<T, D> &b);

	template <class T, size_t D>
	inline pl::math::Vector<T, D> operator-(pl::math::Vector<T, D> a, const pl::math::Vector<T, D> &b);

	template <class T, size_t D>
	inline pl::math::Vector<T, D> operator*(pl::math::Vector<T, D> vector, T value);

	template <class T, size_t D>
	inline pl::math::Vector<T, D> operator/(pl::math::Vector<T, D> vector, T value);

	template <class T, size_t D>
	T operator*(const pl::math::Vector<T, D> &a, const pl::math::Vector<T, D> &b);

	template <class T, size_t D>
	std::ostream &operator<<(std::ostream &stream, const pl::math::Vector<T, D> &vector);



	template <class T, size_t D>
	inline T dot(const pl::math::Vector<T, D> &a, const pl::math::Vector<T, D> &b);

	template <class T, size_t D>
	T length(const pl::math::Vector<T, D> &vector);

	template <class T, size_t D>
	inline T unit(const pl::math::Vector<T, D> &vector);


} // namespace pl::math


#include "vector.inl"

#include "vec2.hpp"