#pragma once

#include <string>


namespace pl::graphics
{
	enum class ShaderType
	{
		vertex,
		fragment,
		geometry
	};

	struct Shader
	{
		pl::graphics::ShaderType type;
		std::string file;
		std::string entryPoint;
	};
	
} // namespace pl::graphics
