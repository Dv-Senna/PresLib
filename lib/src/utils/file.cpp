#include <string>

#include "utils/file.hpp"



namespace pl::utils
{
	std::ofstream loadWriteFile(const std::string &path)
	{
		std::ofstream file {path};
		if (!file)
			throw std::runtime_error("PL : Can't open write file '" + path + "'");

		return file;
	}



	std::ifstream loadReadFile(const std::string &path)
	{
		std::ifstream file {path};
		if (!file)
			throw std::runtime_error("PL : Can't open read file '" + path + "'");

		return file;
	}



	std::unique_ptr<char> readContentFromFile(std::ifstream &file)
	{
		std::string content {};
		std::string line {};

		while (std::getline(file, line))
			content += line + "\n";

		std::unique_ptr<char> contentPtr {new char[content.size() + 1]};
		memcpy(contentPtr.get(), content.data(), content.size() + 1);

		return contentPtr;
	}


} // namespace pl::utils
