#pragma once

#include <string>
#include <vector>


namespace pl::utils
{
	std::vector<unsigned char> getBinaryFileContent(const std::string &path);
	
} // namespace pl::utils
