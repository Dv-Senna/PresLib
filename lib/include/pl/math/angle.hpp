#pragma once

#include <numbers>


namespace pl::math
{
	inline float toDeg(float rad)
	{
		return 180.f * rad / std::numbers::pi;
	}


	inline float toRad(float deg)
	{
		return std::numbers::pi * deg / 180.f;
	}


} // namespace pl::math
