#include <fstream>

#include "utils/file.hpp"



namespace pl::utils
{
	std::vector<unsigned char> getBinaryFileContent(const std::string &path)
	{
		std::ifstream file {path, std::ios::binary};
		if (!file)
			throw std::runtime_error("PL : Can't open file '" + path + "' in binary mode");
		return std::vector<unsigned char> (std::istreambuf_iterator<char> (file), {});
	}
	
} // namespace pl::utils
