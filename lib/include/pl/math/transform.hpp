#pragma once

#include "mat2.hpp"
#include "vec2.hpp"


namespace pl::math
{
	pl::math::Mat2 rotate(pl::math::Mat2 matrix, float angle);
	pl::math::Mat2 scale(pl::math::Mat2 matrix, const pl::math::Vec2 &scaleFactors);

} // namespace pl::math
