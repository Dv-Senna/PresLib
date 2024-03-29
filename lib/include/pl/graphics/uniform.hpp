#pragma once

#include <any>
#include <string>
#include <vector>


namespace pl::graphics
{
	enum class UniformFieldType
	{
		floating, integer,
		vec2, vec3, vec4, mat4
	};

	struct UniformField
	{
		pl::graphics::UniformFieldType type;
		std::string name;
	};

	struct UniformFieldValue
	{
		std::string name;
		std::any value;
	};

	using UniformsFormat = std::vector<pl::graphics::UniformField>;

	struct Uniform
	{
		pl::graphics::UniformsFormat formats;
		std::string name;
		int bindingPoint;
	};

} // namespace pl::graphics
