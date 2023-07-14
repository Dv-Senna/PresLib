#pragma once

#include "../args/args.hpp"
#include "../math/vector.hpp"
#include "../renderMethod.hpp"
#include "../utils/color.hpp"


namespace pl::states
{
	struct Ellipse
	{
		pl::math::Vec2f center;
		float radius;
		float excentricity = 0.f;
		float angle = 0.f;
		pl::utils::Color color = pl::utils::undefined;
		pl::RenderMethod drawingMethod = pl::RenderMethod::fill;
		float borderThickness = 4.f;
	};


	template <class ...Args>
	pl::states::Ellipse createStateFromTemplates(pl::math::Vec2f center, float radius, Args ...args)
	{
		pl::states::Ellipse state {center, radius};

		([&]()
		{
			if constexpr (std::is_same_v<Args, pl::args::excentricity>)
				state.excentricity = args.value;

			else if constexpr (std::is_same_v<Args, pl::args::angle>)
				state.angle = args.value;

			else if constexpr (std::is_same_v<Args, pl::args::color>)
				state.color = args.value;

			else if constexpr (std::is_same_v<Args, pl::args::drawingMethod>)
				state.drawingMethod = args.value;

			else if constexpr (std::is_same_v<Args, pl::args::borderThickness>)
				state.borderThickness = args.value;
		} (), ...);

		return state;
	}


} // namespace pl::states
