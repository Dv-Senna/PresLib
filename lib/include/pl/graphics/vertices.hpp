#pragma once

#include <cinttypes>
#include <map>
#include <vector>


namespace pl::graphics
{
	using VerticesData = std::vector<float>;

	enum class VerticesUsage
	{
		streamDraw,
		staticDraw,
		dynamicDraw
	};

	struct VerticesAttribFormat
	{
		uint32_t location;
		uint32_t dimension;
		uint32_t start = 0;
		bool enable = true;
	};

	enum class VerticesChannel
	{
		position,
		color,
		textureCoord0,
		normal
	};

	struct VerticesFormat
	{
		std::map<pl::graphics::VerticesChannel, pl::graphics::VerticesAttribFormat> channels {
			{pl::graphics::VerticesChannel::position, {0, 2, 0, true}},
			{pl::graphics::VerticesChannel::color, {0, 0, 0, false}},
			{pl::graphics::VerticesChannel::textureCoord0, {0, 0, 0, false}},
			{pl::graphics::VerticesChannel::normal, {0, 0, 0, false}}
		};
		VerticesUsage usage {pl::graphics::VerticesUsage::staticDraw};
	};

	struct Vertices
	{
		pl::graphics::VerticesData data {};
		pl::graphics::VerticesFormat format {};
	};

} // namespace pl::graphics
