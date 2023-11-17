#pragma once

#include <vector>

#include "shader.hpp"
#include "uniform.hpp"
#include "vertices.hpp"
#include "../utils/id.hpp"


namespace pl::graphics
{
	struct Pipeline
	{
		std::vector<pl::utils::Id> shaders {};
		std::vector<pl::graphics::Uniform> uniforms {};
		pl::graphics::VerticesFormat format {};
	};
	
} // namespace pl::graphics
