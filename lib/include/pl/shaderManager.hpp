#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "shader.hpp"


namespace pl
{
	class ShaderManager final
	{
		public:
			ShaderManager();
			~ShaderManager();

			void addShader(const std::string &name, const std::string &path);
			pl::Shader &getShader(const std::string &name);


		private:
			std::unordered_map<std::string, std::unique_ptr<pl::Shader>> m_shaders;
	};

} // namespace pl
