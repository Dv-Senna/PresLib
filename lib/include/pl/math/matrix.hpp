#pragma once

#include <array>
#include <cinttypes>
#include <ostream>


namespace pl::math
{
	template <class T, size_t R, size_t C>
	class Matrix
	{
		public:
			Matrix();
			Matrix(T value);
			template <class ...Args>
			Matrix(T first, Args ...args);
			virtual ~Matrix() = default;

			Matrix(const pl::math::Matrix<T, R, C> &matrix);
			const pl::math::Matrix<T, R, C> &operator=(const pl::math::Matrix<T, R, C> &matrix);

			Matrix(pl::math::Matrix<T, R, C> &&matrix) noexcept;
			const pl::math::Matrix<T, R, C> &operator=(pl::math::Matrix<T, R, C> &&matrix) noexcept;


			inline std::array<T, C> &operator[](size_t row);
			inline const std::array<T, C> &operator[](size_t row) const noexcept;

			inline std::array<std::array<T, C>, R> &get() noexcept;

			const pl::math::Matrix<T, R, C> &operator+=(const pl::math::Matrix<T, R, C> &matrix);
			const pl::math::Matrix<T, R, C> &operator-=(const pl::math::Matrix<T, R, C> &matrix);

			const pl::math::Matrix<T, R, C> &operator*=(T value);
			const pl::math::Matrix<T, R, C> &operator/=(T value);


		protected:
			std::array<std::array<T, C>, R> m_datas;
	};


	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator+(pl::math::Matrix<T, R, C> a, const pl::math::Matrix<T, R, C> &b);
	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator-(pl::math::Matrix<T, R, C> a, const pl::math::Matrix<T, R, C> &b);
	template <class T, size_t R, size_t N, size_t C>
	pl::math::Matrix<T, R, C> operator*(const pl::math::Matrix<T, R, N> &a, const pl::math::Matrix<T, N, C> &b);
	
	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator*(pl::math::Matrix<T, R, C> a, T value);
	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, R, C> operator/(pl::math::Matrix<T, R, C> a, T value);

	template <class T, size_t R, size_t C>
	std::ostream &operator<<(std::ostream &stream, const pl::math::Matrix<T, R, C> &a);


	template <class T, size_t R, size_t C>
	pl::math::Matrix<T, C, R> transpose(const pl::math::Matrix<T, R, C> &matrix);


} // namespace pl::math


#include "matrix.inl"

#include "matn.hpp"