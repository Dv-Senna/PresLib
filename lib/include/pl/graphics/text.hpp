#pragma once

#include <string>
#include <vector>

#include "../instance.hpp"
#include "../utils/id.hpp"


namespace pl::graphics
{
	std::vector<pl::utils::Id> generateVerticesFromText(
		pl::Instance &instance,
		const std::string &font,
		int size,
		const std::string &text,
		std::vector<pl::utils::Id> &textures
	);
	
} // namespace pl::graphics
