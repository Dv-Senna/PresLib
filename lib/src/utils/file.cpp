#include <fstream>

#include "utils/file.hpp"



namespace pl::utils
{
	std::vector<unsigned char> getBinaryFileContent(const std::string &path)
	{
		std::ifstream file {path, std::ios::binary};
		return std::vector<unsigned char> (std::istreambuf_iterator<char> (file), {});
	}
	
} // namespace pl::utils
