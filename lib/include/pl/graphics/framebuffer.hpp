#pragma once

#include <glm/glm.hpp>

#include "texture.hpp"


namespace pl::graphics
{
	enum class DepthStencilFormat
	{
		depth24stencil8,
		none
	};

	struct Framebuffer
	{
		glm::vec2 size;
		int multisample {4};
		pl::graphics::ColorFormat colorFormat {pl::graphics::ColorFormat::r8g8b8};
		pl::graphics::DepthStencilFormat depthStencilFormat {pl::graphics::DepthStencilFormat::depth24stencil8};
		pl::graphics::Filter minFilter {pl::graphics::Filter::nearest};
		pl::graphics::Filter magFilter {pl::graphics::Filter::nearest};
	};

	enum class CleanFlag
	{
		color =   0b001,
		depth =   0b010,
		stencil = 0b100,

		__last = 3
	};

} // namespace pl::graphics
