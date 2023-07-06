#pragma once

#include "matrix.hpp"


namespace pl::math
{
	template <class T, size_t N>
	class Matn : public pl::math::Matrix<T, N, N>
	{
		public:
			Matn();
			Matn(T value);
			template <class ...Args>
			Matn(T first, Args ...args);
			virtual ~Matn() = default;
	};


	template <class T, size_t N>
	T det(const pl::math::Matn<T, N> &matrix);


} // namespace pl::math


#include "matn.inl"

#include "mat2.hpp"
#include "mat3.hpp"