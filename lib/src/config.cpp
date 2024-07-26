#include "pl/config.hpp"



namespace pl {
	void Config::setShaderFolderPath(const std::filesystem::path &path) {
		s_shaderFolderPath = path;
	}


	const std::filesystem::path &Config::getShaderFolderPath() {
		return s_shaderFolderPath;
	}


	void Config::setImageFolderPath(const std::filesystem::path &path) {
		s_imageFolderPath = path;
	}


	const std::filesystem::path &Config::getImageFolderPath() {
		return s_imageFolderPath;
	}


	void Config::setCustomRenderCallback(const std::function<void()> &callback) {
		s_customRenderCallback = callback;
	}


	const std::function<void()> &Config::getCustomRenderCallback() {
		return s_customRenderCallback;
	}


	void Config::setFramerate(pl::Uint fps) {
		s_framerate = fps;
		s_frameDuration = 1000.f / static_cast<pl::Float> (fps);
	}


	const pl::Uint &Config::getFramerate() {
		return s_framerate;
	}


	const pl::Float &Config::getFrameDuration() {
		return s_frameDuration;
	}


	std::filesystem::path Config::s_shaderFolderPath {"shaders/"};
	std::filesystem::path Config::s_imageFolderPath {"images/"};
	std::function<void()> Config::s_customRenderCallback {nullptr};
	pl::Uint Config::s_framerate {60};
	pl::Float Config::s_frameDuration {1000.f/60.f};

} // namespace pl
