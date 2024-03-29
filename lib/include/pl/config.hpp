#pragma once

#include <string>

#include <glm/glm.hpp>

#include "graphics/api.inl"
#include "graphics/projection.hpp"
#include "utils/color.hpp"


namespace pl::config
{
	inline const glm::vec2 openglVersion {4, 6};
	inline const pl::utils::Color openglBitsPerColor {8, 8, 8};
	inline const bool useMSAA {true};
	inline const int MSAASamplesCount {4};
	inline const glm::vec2 defaultViewportSize {1920, 1080};
	inline const pl::graphics::Api defaultGraphicsApi {pl::graphics::Api::OpenGL};
	inline const std::string defaultPresentationTitle {"PresLib"};
	inline const pl::graphics::Projection defaultProjection {pl::graphics::Projection::ortho};
	inline const std::string texFolder {"./latex/"};

} // namespace pl::config
