#pragma once

#include <string>

#include "../args/args.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"



namespace pl::states
{
	struct Math
	{
		std::string equation;
		pl::math::Vec2f position;
		float size;
		pl::utils::Color color = pl::utils::undefined;
		float angle = 0.f;
		pl::math::Vec2f distortion {1.f, 1.f};



		template <class ...Args>
		static pl::states::Math createStateFromTemplates(const std::string &equation, const pl::math::Vec2f &pos, float size, Args ...args)
		{
			pl::states::Math state {equation, pos, size};

			([&]()
			{
				if constexpr (std::is_same_v<Args, pl::args::Color>)
					state.color = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Angle>)
					state.angle = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::Distortion>)
					state.distortion = args.value;
			} (), ...);

			return state;
		}
	};
} // namespace pl::states
