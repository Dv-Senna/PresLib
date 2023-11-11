#pragma once

#include <glm/glm.hpp>

#include "utils/color.hpp"


namespace pl
{
	struct StyleColor
	{
		
	};

	struct Style
	{
		struct Color
		{
			pl::utils::Color text {pl::utils::black};
			pl::utils::Color background {100, 100, 100, 255};
			pl::utils::Color shape {pl::utils::orange};
		};

		pl::Style::Color colors;
	};

} // namespace pl
