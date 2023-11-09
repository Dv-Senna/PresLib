#pragma once

#include <string>

#include "../instance.hpp"
#include "id.hpp"


namespace pl::utils
{
	pl::utils::Id loadImage(pl::Instance &instance, const std::string &path, glm::vec2 &size);
	
} // namespace pl::utils
