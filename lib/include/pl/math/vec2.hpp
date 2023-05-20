#pragma once

#include <ostream>


namespace pl::math
{
	/// @brief A class that handle 2D vector
	struct Vec2
	{
		float x, y;

		inline pl::math::Vec2 &operator+=(const pl::math::Vec2 &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			return *this;
		}

		inline pl::math::Vec2 &operator-=(const pl::math::Vec2 &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			return *this;
		}
	};

	inline pl::math::Vec2 operator+(pl::math::Vec2 vec1, const pl::math::Vec2 &vec2)
	{
		vec1 += vec2;
		return vec1;
	}

	inline pl::math::Vec2 operator-(pl::math::Vec2 vec1, const pl::math::Vec2 &vec2)
	{
		vec1 -= vec2;
		return vec1;
	}


	inline std::ostream &operator<<(std::ostream &stream, const pl::math::Vec2 &vec)
	{
		stream << "(" << vec.x << ", " << vec.y << ")";
		return stream;
	}
	
} // namespace pl::math
