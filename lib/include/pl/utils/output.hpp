#pragma once

#include <ostream>
#include <string>

#include <glm/glm.hpp>


namespace pl::utils
{
	void output(std::ostream &stream, const std::string &name, const glm::mat4 &matrix);
} // namespace pl::utils
