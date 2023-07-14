#pragma once

#include "../math/vector.hpp"
#include "../renderMethod.hpp"
#include "../utils/color.hpp"


namespace pl::args
{
	struct excentricity {float value;};
	struct angle {float value;};
	struct color {pl::utils::Color value;};
	struct drawingMethod {pl::RenderMethod value;};
	struct borderThickness {float value;};

} // namespace pl::args
