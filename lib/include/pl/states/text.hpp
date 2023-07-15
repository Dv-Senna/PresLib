#pragma once

#include <string>

#include "../args/args.hpp"
#include "../math/vector.hpp"


namespace pl::states
{
	struct Text
	{
		std::string text;
		std::string font;
		pl::math::Vec2f position;
		float size;
		pl::utils::Color color = pl::utils::undefined;
		float angle = 0.f;
		pl::math::Vec2f distortion {1.f, 1.f};



		template <class ...Args>
		static pl::states::Text createStateFromTemplates(
			const std::string &text,
			const std::string &font,
			const pl::math::Vec2f &pos,
			float size,
			Args ...args
		)
		{
			pl::states::Text state {text, font, pos, size};

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
