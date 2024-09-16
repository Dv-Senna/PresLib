#include "pl/utils/files.hpp"



namespace pl::utils {
	std::vector<pl::Byte> readBinaryFile(std::ifstream &file) {
		std::vector<pl::Byte> buffer {std::istreambuf_iterator<char> (file), {}};
		return buffer;
	}


} // namespace pl::utils
