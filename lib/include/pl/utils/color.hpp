#pragma once

#include <cinttypes>
#include <ostream>

#include <SDL2/SDL.h>


namespace pl::utils
{
	struct Color
	{
		uint8_t r, g, b, a = 255;
		bool undefined = false;

		bool operator==(const pl::utils::Color &color) const noexcept
		{
			return r == color.r && g == color.g && b == color.b && a == color.a && undefined == color.undefined;
		}

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

		operator uint32_t()
		{
			return r * 0x1000000 + g * 0x10000 + b * 0x100 + a;
		}

		operator uint32_t() const
		{
			return r * 0x1000000 + g * 0x10000 + b * 0x100 + a;
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
	inline pl::utils::Color yellow {255, 255, 0};
	inline pl::utils::Color aqua {0, 255, 255};
	inline pl::utils::Color magenta {255, 0, 255};
	inline pl::utils::Color orange {255, 125, 0};
	inline pl::utils::Color purple {125, 0, 255};
	inline pl::utils::Color transparent {0, 0, 0, 0};
	inline pl::utils::Color undefined {0, 0, 0, 0, true};


} // namespace pl::utils

