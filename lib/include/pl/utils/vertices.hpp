#pragma once

#include <cinttypes>
#include <map>
#include <vector>


namespace pl::utils
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
		std::map<pl::utils::VerticesChannel, pl::utils::VerticesAttribFormat> channels {
			{pl::utils::VerticesChannel::position, {0, 2, 0, true}},
			{pl::utils::VerticesChannel::color, {0, 0, 0, false}},
			{pl::utils::VerticesChannel::textureCoord0, {0, 0, 0, false}},
			{pl::utils::VerticesChannel::normal, {0, 0, 0, false}}
		};
		VerticesUsage usage {pl::utils::VerticesUsage::staticDraw};
	};

	struct Vertices
	{
		pl::utils::VerticesData data {};
		pl::utils::VerticesFormat format {};
	};

} // namespace pl::utils
