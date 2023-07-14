#pragma once

#include <string>

#include "../args/args.hpp"
#include "../math/vector.hpp"


namespace pl::states
{
	struct Image
	{
		std::string path;
		pl::math::Vec2f position;
		float scale = 1.f;
		pl::math::Vec2f distortion {1.f, 1.f};



		template <class ...Args>
		static pl::states::Image createStateFromTemplates(const std::string &path, const pl::math::Vec2f &pos, Args ...args)
		{
			pl::states::Image state {path, pos};

			([&]()
			{
				if constexpr (std::is_same_v<Args, pl::args::scale>)
					state.scale = args.value;

				else if constexpr (std::is_same_v<Args, pl::args::distortion>)
					state.distortion = args.value;
			} (), ...);

			return state;
		}
	};



} // namespace pl::states
