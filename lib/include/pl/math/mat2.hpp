#pragma once

#include "matn.hpp"


namespace pl::math
{
	template <class T>
	class Mat2 final : public pl::math::Matn<T, 2>
	{
		public:
			Mat2() : Matn<T, 2> ()
			{

			}



			Mat2(T value) : Matn<T, 2> (value)
			{

			}



			template <class ...Args>
			Mat2(T first, Args ...args) : Matn<T, 2> (first, args...)
			{

			}
	};


	using Mat2f = pl::math::Mat2<float>;
	using Mat2d = pl::math::Mat2<double>;
	using Mat2i8 = pl::math::Mat2<int8_t>;
	using Mat2u8 = pl::math::Mat2<uint8_t>;
	using Mat2i16 = pl::math::Mat2<int16_t>;
	using Mat2u16 = pl::math::Mat2<uint16_t>;
	using Mat2i32 = pl::math::Mat2<int32_t>;
	using Mat2u32 = pl::math::Mat2<uint32_t>;
	using Mat2i64 = pl::math::Mat2<int64_t>;
	using Mat2u64 = pl::math::Mat2<uint64_t>;
	using Mat2i = pl::math::Mat2i32;
	using Mat2u = pl::math::Mat2u32;

} // namespace pl::math
