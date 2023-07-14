#pragma once

#include "../math/vector.hpp"
#include "../renderMethod.hpp"
#include "../utils/color.hpp"


namespace pl {using degrees = float;}

namespace pl::args
{
	struct excentricity {float value;};
	struct angle {pl::degrees value;};
	struct color {pl::utils::Color value;};
	struct drawingMethod {pl::RenderMethod value;};
	struct borderThickness {float value;};
	struct scale {float value;};
	struct distortion {pl::math::Vec2f value;};
	struct opacity {float value;};

} // namespace pl::args
