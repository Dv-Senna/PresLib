#pragma once

#include "../math/vector.hpp"
#include "../renderMethod.hpp"
#include "../tipShape.hpp"
#include "../utils/color.hpp"


namespace pl {using degrees = float;}

namespace pl::args
{
	struct Excentricity {float value; pl::args::Excentricity operator=(float v) {value = v; return *this;}};
	struct Angle {pl::degrees value; pl::args::Angle operator=(float v) {value = v; return *this;}};
	struct Color {pl::utils::Color value; pl::args::Color operator=(const pl::utils::Color &v) {value = v; return *this;}};
	struct RenderMethod {pl::RenderMethod value; pl::args::RenderMethod operator=(pl::RenderMethod v) {value = v; return *this;}};
	struct BorderThickness {float value; pl::args::BorderThickness operator=(float v) {value = v; return *this;}};
	struct Scale {float value; pl::args::Scale operator=(float v) {value = v; return *this;}};
	struct Distortion {pl::math::Vec2f value; pl::args::Distortion operator=(const pl::math::Vec2f &v) {value = v; return *this;}};
	struct Opacity {float value; pl::args::Opacity operator=(float v) {value = v; return *this;}};
	struct Thickness {float value; pl::args::Thickness operator=(float v) {value = v; return *this;}};
	struct StartTipShape {pl::TipShape value; pl::args::StartTipShape operator=(pl::TipShape v) {value = v; return *this;}};
	struct EndTipShape {pl::TipShape value; pl::args::EndTipShape operator=(pl::TipShape v) {value = v; return *this;}};
	struct TipShape {pl::TipShape value; pl::args::TipShape operator=(pl::TipShape v) {value = v; return *this;}};

	inline pl::args::Excentricity excentricity {0.f};
	inline pl::args::Angle angle {0.f};
	inline pl::args::Color color {pl::utils::undefined};
	inline pl::args::RenderMethod rendergMethod {pl::RenderMethod::fill};
	inline pl::args::BorderThickness borderThickness {0.f};
	inline pl::args::Scale scale {0.f};
	inline pl::args::Distortion distortion {{0.f, 0.f}};
	inline pl::args::Opacity opacity {0.f};
	inline pl::args::Thickness thickness {0.f};
	inline pl::args::StartTipShape startTipShape {pl::TipShape::flat};
	inline pl::args::EndTipShape endTipShape {pl::TipShape::flat};
	inline pl::args::TipShape tipShape {pl::TipShape::flat};

} // namespace pl::args
