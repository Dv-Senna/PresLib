#pragma once

#include <memory>

#include <glm/glm.hpp>


namespace pl::graphics
{
	enum class Filter
	{
		nearest,
		linear
	};


	enum class TextureFormat
	{
		r8g8b8, r8g8b8a8
	};


	struct Texture
	{
		glm::vec2 size;
		std::shared_ptr<unsigned char> pixels {};
		pl::graphics::TextureFormat format {pl::graphics::TextureFormat::r8g8b8};
		pl::graphics::Filter minFilter {pl::graphics::Filter::linear};
		pl::graphics::Filter magFilter {pl::graphics::Filter::linear};
	};

} // namespace pl::graphics
