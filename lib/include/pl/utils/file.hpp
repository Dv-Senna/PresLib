#pragma once

#include <fstream>
#include <string>


namespace pl::utils
{
	std::ofstream loadWriteFile(const std::string &path);
	std::ifstream loadReadFile(const std::string &path);

	std::string readContentFromFile(std::ifstream &file);

} // namespace pl::utils
