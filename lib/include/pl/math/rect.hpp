#pragma once

#include <ostream>


namespace pl::math
{
	struct Rect
	{
		float x, y, w, h;
	};

	inline std::ostream &operator<<(std::ostream &stream, const pl::math::Rect &rect)
	{
		stream << "(" << rect.x << ", " << rect.y << " | " << rect.w << "x" << rect.h << ")";
		return stream;
	}

} // namespace pl::math
