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
		pl::TipShape startTipShape;
		pl::TipShape endTipShape;


		template <class ...Args>
		static pl::states::Line createStateFromTemplates(
			const pl::math::Vec2f &start,
			const pl::math::Vec2f &end,
			Args ...args)
		{
			pl::states::Line state {start, end};

			([&]()
			{
				if constexpr (std::is_same_v<Args, pl::args::color>)
					state.color = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::scale>)
					state.scale = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::distortion>)
					state.distortion = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::thickness>
					|| std::is_same_v<Args, pl::args::borderThickness>
				)
					state.thickness = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::startTipShape>)
					state.startTipShape = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::endTipShape>)
					state.endTipShape = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::tipShape>)
				{
					state.startTipShape = args.value;
					state.endTipShape = args.value;
				}

			} (), ...);

			return state;
		}
	};



} // namespace pl::states
