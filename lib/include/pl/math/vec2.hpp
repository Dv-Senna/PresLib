#pragma once



namespace pl::math
{
	struct Vec2
	{
		float x, y;

		inline pl::math::Vec2 &operator+=(pl::math::Vec2 &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			return *this;
		}

		inline pl::math::Vec2 &operator-=(pl::math::Vec2 &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			return *this;
		}
	};

	inline pl::math::Vec2 &operator+(pl::math::Vec2 vec1, pl::math::Vec2 &vec2)
	{
		vec1 += vec2;
		return vec1;
	}

	inline pl::math::Vec2 &operator-(pl::math::Vec2 vec1, pl::math::Vec2 &vec2)
	{
		vec1 -= vec2;
		return vec1;
	}
	
} // namespace pl::math
