#pragma once

#include <cinttypes>
#include <ostream>


namespace pl::utils
{
	struct Color
	{
		uint8_t r, g, b, a = 255;
	};


	inline std::ostream &operator<<(std::ostream &stream, const pl::utils::Color &color)
	{
		stream << "(r = " << color.r << ", g = " << color.g << ", b = " << color.b << ", a = " << color.a << ")";
		return stream;
	}


	inline pl::utils::Color red {255, 0, 0};
	inline pl::utils::Color green {0, 255, 0};
	inline pl::utils::Color blue {0, 255, 0};
	inline pl::utils::Color white {255, 255, 255};
	inline pl::utils::Color black {255, 255, 255};
	inline pl::utils::Color transparent {0, 0, 0, 0};


} // namespace pl::utils

