#pragma once

#include "vector.hpp"


namespace pl::math
{
	template <class T>
	class Vec3 : public pl::math::Vector<T, 3>
	{
		public:
			Vec3() : pl::math::Vector<T, 3> (), x {this->m_datas[0]}, y {this->m_datas[1]}, z {this->m_datas[2]}
			{

			}

			Vec3(T _x, T _y, T _z) : pl::math::Vec3<T> ()
			{
				x = _x;
				y = _y;
				z = _z;
			}

			~Vec3() = default;

			T &x, &y, &z;
	};


	using Vec3f = pl::math::Vec3<float>;
	using Vec3d = pl::math::Vec3<double>;
	using Vec3i8 = pl::math::Vec3<int8_t>;
	using Vec3u8 = pl::math::Vec3<uint8_t>;
	using Vec3i16 = pl::math::Vec3<int16_t>;
	using Vec3u16 = pl::math::Vec3<uint16_t>;
	using Vec3i32 = pl::math::Vec3<int32_t>;
	using Vec3u32 = pl::math::Vec3<uint32_t>;
	using Vec3i64 = pl::math::Vec3<int64_t>;
	using Vec3u64 = pl::math::Vec3<uint64_t>;
	using Vec3i = pl::math::Vec3i32;
	using Vec3u = pl::math::Vec3u32;

} // namespace pl::math
