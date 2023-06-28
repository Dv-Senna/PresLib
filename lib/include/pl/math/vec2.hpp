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

			Vec2(T _x, T _y) : pl::math::Vector<T, 2> (), x {this->m_datas[0]}, y {this->m_datas[1]}
			{
				x = _x;
				y = _y;
			}

			~Vec2() = default;

			T &x, &y;
	};

} // namespace pl::math
