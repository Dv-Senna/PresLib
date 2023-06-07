#define CATCH_CONFIG_MAIN
#include "catch2.hpp"


#include "pl/math/mat2.hpp"
#include "pl/math/vec2.hpp"


TEST_CASE("2D vector arithmetic", "[vec2]")
{
	pl::math::Vec2 vec {1, 1};
	vec *= 2;

	REQUIRE(vec == pl::math::Vec2(2, 2));

	vec += pl::math::Vec2(3, -2);
	REQUIRE(vec == pl::math::Vec2(5, 0));

	vec -= pl::math::Vec2(3, -2);
	REQUIRE(vec == pl::math::Vec2(2, 2));
}


TEST_CASE("2x2 Matrix arithmetic", "[mat2]")
{
	pl::math::Mat2 matrix {1, 2, 3, 4};
	matrix *= 3;

	REQUIRE(matrix == pl::math::Mat2(3, 6, 9, 12));

	matrix += matrix;

	REQUIRE(matrix == pl::math::Mat2(6, 12, 18, 24));
	REQUIRE(pl::math::det(matrix) == -72);
	REQUIRE(pl::math::inverse(matrix) == pl::math::Mat2(-24.0f / 72.0f, 12.0f / 72.0f, 18.0f / 72.0f, -6.0f / 72.0f));

	matrix *= matrix;

	REQUIRE(matrix == pl::math::Mat2(252, 360, 540, 792));
}