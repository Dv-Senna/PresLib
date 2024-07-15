#include "pl/config.hpp"



namespace pl {
	void Config::setShaderFolderPath(const std::string &path) {
		s_shaderFolderPath = path;
		if (s_shaderFolderPath.size() == 0)
			return;

		if (s_shaderFolderPath[s_shaderFolderPath.size() - 1] != '/')
			s_shaderFolderPath.push_back('/');
	}


	const std::string &Config::getShaderFolderPath() {
		return s_shaderFolderPath;
	}


	std::string Config::s_shaderFolderPath {"shaders/"};

} // namespace pl
