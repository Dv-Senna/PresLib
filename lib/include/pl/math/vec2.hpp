#pragma once

#include "vector.hpp"


namespace pl::math
{
	template <class T>
	class Vec2 : public pl::math::Vector<T, 2>
	{
		public:
			Vec2() : pl::math::Vector<T, 2> (), x {this->m_datas[0]}, y {this->m_datas[1]}
			{

			}

			Vec2(T _x, T _y) : pl::math::Vec2<T> ()
			{
				x = _x;
				y = _y;
			}

			Vec2(const pl::math::Vec2<T> &vector) : Vec2(vector.x, vector.y)
			{

			}

			const pl::math::Vec2<T> &operator=(const pl::math::Vec2<T> &vector)
			{
				x = vector.x;
				y = vector.y;

				return *this;
			}

			~Vec2() = default;

			T &x, &y;
	};


	using Vec2f = pl::math::Vec2<float>;
	using Vec2d = pl::math::Vec2<double>;
	using Vec2i8 = pl::math::Vec2<int8_t>;
	using Vec2u8 = pl::math::Vec2<uint8_t>;
	using Vec2i16 = pl::math::Vec2<int16_t>;
	using Vec2u16 = pl::math::Vec2<uint16_t>;
	using Vec2i32 = pl::math::Vec2<int32_t>;
	using Vec2u32 = pl::math::Vec2<uint32_t>;
	using Vec2i64 = pl::math::Vec2<int64_t>;
	using Vec2u64 = pl::math::Vec2<uint64_t>;
	using Vec2i = pl::math::Vec2i32;
	using Vec2u = pl::math::Vec2u32;

} // namespace pl::math
