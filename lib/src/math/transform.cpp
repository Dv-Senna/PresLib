#include <cmath>

#include "math/transform.hpp"



namespace pl::math
{
	pl::math::Mat2 rotate(pl::math::Mat2 matrix, float angle)
	{
		matrix = pl::math::Mat2(cos(angle), -sin(angle), sin(angle), cos(angle)) * matrix;
		return matrix;
	}


	pl::math::Mat2 scale(pl::math::Mat2 matrix, const pl::math::Vec2 &scaleFactors)
	{
		matrix = pl::math::Mat2(scaleFactors.x, 0, 0, scaleFactors.y);
		return matrix;
	}


} // namespace pl::math
