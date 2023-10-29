#pragma once

#include <string>

#include "graphics/api.inl"
#include "math/vec2.hpp"
#include "utils/color.hpp"


namespace pl::config
{
	inline const pl::math::Vec2i8 openglVersion {4, 6};
	inline const pl::utils::Color openglBitsPerColor {8, 8, 8};
	inline const bool useMSAA {true};
	inline const int MSAASamplesCount {4};
	inline const pl::math::Vec2i defaultViewportSize {1920, 1080};
	inline const pl::graphics::Api defaultGraphicsApi {pl::graphics::Api::OpenGL};
	inline const std::string defaultPresentationTitle {"PresLib"};

} // namespace pl::config
