#pragma once

#include <string>

#include "math/vector.hpp"
#include "utils/color.hpp"


namespace pl
{
	namespace impl
	{
		class Block;
	}

	struct Style
	{
		pl::impl::Block *background;
		pl::impl::Block *foreground;
		pl::utils::Color textColor;
		pl::utils::Color titleColor;
		pl::utils::Color objectColor;
		pl::utils::Color backgroundColor;
		pl::utils::Color mainColor;
		pl::utils::Color secondColor;
		pl::utils::Color thirdColor;
		pl::math::Vec2f titlePosition;
		float titleSize;
		std::string titleFont;
	};

} // namespace pl
