#pragma once

#include <filesystem>
#include <functional>
#include <string>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl {
	class PL_CORE Config {
		public:
			static void setShaderFolderPath(const std::filesystem::path &path);
			static const std::filesystem::path &getShaderFolderPath();

			static void setImageFolderPath(const std::filesystem::path &path);
			static const std::filesystem::path &getImageFolderPath();

			static void setCustomRenderCallback(const std::function<void()> &callback);
			static const std::function<void()> &getCustomRenderCallback();

			static void setFramerate(pl::Uint fps);
			static const pl::Uint &getFramerate();
			static const pl::Float &getFrameDuration();

		private:
			static std::filesystem::path s_shaderFolderPath;
			static std::filesystem::path s_imageFolderPath;
			static std::function<void()> s_customRenderCallback;
			static pl::Uint s_framerate;
			static pl::Float s_frameDuration;
	};

} // namespace pl
