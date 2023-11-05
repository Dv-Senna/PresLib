#pragma once

#include <glm/glm.hpp>

#include "types.hpp"


namespace pl::utils
{
	inline glm::mat4 rotate2D(pl::utils::Radians angle);
	inline glm::mat4 translate(const glm::vec2 &offset);
	inline glm::mat4 scale(const glm::vec2 &scale);
	
} // namespace pl::utils


#include "transformation.inl"