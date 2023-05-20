#pragma once

#include <ostream>

#include <SDL2/SDL.h>


namespace pl::math
{
	/// @brief A struct that handle rectangle datas
	struct Rect
	{
		float x, y, w, h;

		inline operator SDL_Rect()
		{
			return {
				static_cast<int> (x),
				static_cast<int> (y),
				static_cast<int> (w),
				static_cast<int> (h)
			};
		}
	};

	inline std::ostream &operator<<(std::ostream &stream, const pl::math::Rect &rect)
	{
		stream << "(" << rect.x << ", " << rect.y << " | " << rect.w << "x" << rect.h << ")";
		return stream;
	}

} // namespace pl::math
