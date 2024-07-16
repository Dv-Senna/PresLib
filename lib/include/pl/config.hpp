#pragma once

#include <functional>
#include <string>

#include "pl/core.hpp"



namespace pl {
	class PL_CORE Config {
		public:
			static void setShaderFolderPath(const std::string &path);
			static const std::string &getShaderFolderPath();

			static void setCustomRenderCallback(const std::function<void()> &callback);
			static const std::function<void()> &getCustomRenderCallback();

		private:
			static std::string s_shaderFolderPath;
			static std::function<void()> s_customRenderCallback;
	};

} // namespace pl
