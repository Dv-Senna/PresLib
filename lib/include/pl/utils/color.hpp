#pragma once

#include <cstdint>
#include <ostream>

#include <SDL2/SDL.h>


namespace pl::utils
{
	struct Color
	{
		uint8_t r, g, b, a = 255;

		inline operator SDL_Color()
		{
			return {this->r, this->g, this->b, this->a};
		}
	};

	inline std::ostream &operator<<(std::ostream &stream, const pl::utils::Color &color)
	{
		stream << "r = " << color.r << ", g = " << color.g << ", b" << color.b << ", a" << color.a;
		return stream;
	}

	inline const pl::utils::Color white {255, 255, 255};
	inline const pl::utils::Color black {0, 0, 0};
	inline const pl::utils::Color red {255, 0, 0};
	inline const pl::utils::Color green {0, 255, 0};
	inline const pl::utils::Color blue {0, 0, 255};
	inline const pl::utils::Color yellow {255, 255, 0};
	inline const pl::utils::Color pink {255, 0, 255};
	inline const pl::utils::Color turquoise {0, 255, 255};

} // namespace pl::utils
