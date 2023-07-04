#pragma once

#include <cinttypes>
#include <ostream>

#include <SDL2/SDL.h>


namespace pl::utils
{
	struct Color
	{
		uint8_t r, g, b, a = 255;

		operator SDL_Color() const
		{
			SDL_Color color {r, g, b, a};
			return color;
		}

		operator SDL_Color()
		{
			SDL_Color color {r, g, b, a};
			return color;
		}
	};


	inline std::ostream &operator<<(std::ostream &stream, const pl::utils::Color &color)
	{
		stream << "(r = " << color.r << ", g = " << color.g << ", b = " << color.b << ", a = " << color.a << ")";
		return stream;
	}


	inline pl::utils::Color red {255, 0, 0};
	inline pl::utils::Color green {0, 255, 0};
	inline pl::utils::Color blue {0, 0, 255};
	inline pl::utils::Color white {255, 255, 255};
	inline pl::utils::Color black {255, 255, 255};
	inline pl::utils::Color transparent {0, 0, 0, 0};


} // namespace pl::utils

