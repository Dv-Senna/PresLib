#pragma once

#include "matn.hpp"


namespace pl::math
{
	template <class T>
	class Mat3 final : public pl::math::Matn<T, 3>
	{
		public:
			Mat3() : Matn<T, 3> ()
			{

			}



			Mat3(T value) : Matn<T, 3> (value)
			{

			}



			template <class ...Args>
			Mat3(T first, Args ...args) : Matn<T, 3> (first, args...)
			{

			}
	};


	using Mat3f = pl::math::Mat3<float>;
	using Mat3d = pl::math::Mat3<double>;
	using Mat3i8 = pl::math::Mat3<int8_t>;
	using Mat3u8 = pl::math::Mat3<uint8_t>;
	using Mat3i16 = pl::math::Mat3<int16_t>;
	using Mat3u16 = pl::math::Mat3<uint16_t>;
	using Mat3i32 = pl::math::Mat3<int32_t>;
	using Mat3u32 = pl::math::Mat3<uint32_t>;
	using Mat3i64 = pl::math::Mat3<int64_t>;
	using Mat3u64 = pl::math::Mat3<uint64_t>;
	using Mat3i = pl::math::Mat3i32;
	using Mat3u = pl::math::Mat3u32;

} // namespace pl::math
