#pragma once

#include "../args/args.hpp"
#include "../math/vector.hpp"
#include "../tipShape.hpp"
#include "../utils/color.hpp"



namespace pl::states
{
	struct Line
	{
		pl::math::Vec2f start;
		pl::math::Vec2f end;
		pl::utils::Color color {pl::utils::undefined};
		float scale = 1.f;
		pl::math::Vec2f distortion {1.f, 1.f};
		float thickness {2.f};
		pl::TipShape startTipShape {pl::TipShape::flat};
		pl::TipShape endTipShape {pl::TipShape::flat};


		template <class ...Args>
		static pl::states::Line createStateFromTemplates(
			const pl::math::Vec2f &start,
			const pl::math::Vec2f &end,
			Args ...args)
		{
			pl::states::Line state {start, end};

			([&]()
			{
				if constexpr (std::is_same_v<Args, pl::args::Color>)
					state.color = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Scale>)
					state.scale = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Distortion>)
					state.distortion = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Thickness>
					|| std::is_same_v<Args, pl::args::BorderThickness>
				)
					state.thickness = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::StartTipShape>)
					state.startTipShape = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::EndTipShape>)
					state.endTipShape = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::TipShape>)
				{
					state.startTipShape = args.value;
					state.endTipShape = args.value;
				}

			} (), ...);

			return state;
		}
	};



} // namespace pl::states
