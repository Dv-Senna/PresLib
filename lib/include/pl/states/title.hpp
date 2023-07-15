#pragma once

#include <string>

#include "../args/args.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"



namespace pl::states
{
	struct Title
	{
		std::string text;
		pl::math::Vec2f position {};
		float size {0.f};
		float angle = 0.f;
		pl::utils::Color color {pl::utils::undefined};
		pl::math::Vec2f distortion {1.f, 1.f};
	};

} // namespace pl::states
