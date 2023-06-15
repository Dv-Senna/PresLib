#pragma once

#include <fstream>
#include <memory>


namespace pl::utils
{
	std::ofstream loadWriteFile(const std::string &path);
	std::ifstream loadReadFile(const std::string &path);

	std::unique_ptr<char> readContentFromFile(std::ifstream &file);

} // namespace pl::utils
