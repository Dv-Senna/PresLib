#pragma once

#include <cstdint>
#include <ostream>


namespace pl::utils
{
	struct Color
	{
		uint8_t r, g, b, a = 255;
	};

	inline std::ostream &operator<<(std::ostream &stream, const pl::utils::Color &color)
	{
		stream << "r = " << color.r << ", g = " << color.g << ", b" << color.b << ", a" << color.a;
		return stream;
	}

} // namespace pl::utils
