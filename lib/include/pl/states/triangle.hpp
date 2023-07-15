#pragma once

#include "../args/args.hpp"
#include "../math/vector.hpp"
#include "../renderMethod.hpp"
#include "../utils/color.hpp"


namespace pl::states
{
	struct Triangle
	{
		pl::math::Vec2f pos1;
		pl::math::Vec2f pos2;
		pl::math::Vec2f pos3;
		pl::utils::Color color {pl::utils::undefined};
		float scale = 1.f;
		float angle = 0.f;
		float borderThickness {2.f};
		pl::math::Vec2f distortion {1.f, 1.f};
		pl::RenderMethod renderMethod {pl::RenderMethod::fill};



		template <class ...Args>
		static pl::states::Triangle createStateFromTemplates(
			const pl::math::Vec2f &pos1,
			const pl::math::Vec2f &pos2,
			const pl::math::Vec2f &pos3,
			Args ...args
		)
		{
			pl::states::Triangle state {pos1, pos2, pos3};

			([&]()
			{
				if constexpr (std::is_same_v<Args, pl::args::Color>)
					state.color = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Scale>)
					state.scale = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Angle>)
					state.angle = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::BorderThickness>)
					state.borderThickness = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Distortion>)
					state.distortion = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::RenderMethod>)
					state.renderMethod = args.value;

			} (), ...);

			return state;
		}
	};



} // namespace pl::states
