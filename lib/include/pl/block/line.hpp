#pragma once

#include "../block.hpp"
#include "math/vec2.hpp"


namespace pl::block
{
	class Line : public pl::Block
	{
		Line(pl::Instance &instance, pl::math::Vec2 start, pl::math::Vec2 end);
		~Line();
	};

} // namespace pl::block
