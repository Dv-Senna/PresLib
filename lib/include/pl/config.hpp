#pragma once

#include <functional>
#include <string>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl {
	class PL_CORE Config {
		public:
			static void setShaderFolderPath(const std::string &path);
			static const std::string &getShaderFolderPath();

			static void setCustomRenderCallback(const std::function<void()> &callback);
			static const std::function<void()> &getCustomRenderCallback();

			static void setFramerate(pl::Uint fps);
			static const pl::Uint &getFramerate();
			static const pl::Float &getFrameDuration();

		private:
			static std::string s_shaderFolderPath;
			static std::function<void()> s_customRenderCallback;
			static pl::Uint s_framerate;
			static pl::Float s_frameDuration;
	};

} // namespace pl
