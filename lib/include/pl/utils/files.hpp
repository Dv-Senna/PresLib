#pragma once

#include <fstream>
#include <vector>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::utils {
	PL_CORE std::vector<pl::Byte> readBinaryFile(std::ifstream &file);

} // namespace pl::utils
