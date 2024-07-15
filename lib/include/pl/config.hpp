#pragma once

#include <string>

#include "pl/core.hpp"



namespace pl {
	class Config {
		public:
			static void setShaderFolderPath(const std::string &path);
			static const std::string &getShaderFolderPath();

		private:
			static std::string s_shaderFolderPath;
	};

} // namespace pl
