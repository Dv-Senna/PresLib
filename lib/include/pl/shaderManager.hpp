#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "opengl/shader.hpp"


namespace pl
{
	class ShaderManager final
	{
		public:
			ShaderManager();
			~ShaderManager();

			void addShader(const std::string &name, const std::string &path);
			pl::opengl::Shader &getShader(const std::string &name);

			void use(const std::string &name);
			pl::opengl::Shader &getCurrent();


		private:
			std::unordered_map<std::string, std::unique_ptr<pl::opengl::Shader>> m_shaders;
			pl::opengl::Shader *m_current;
	};

} // namespace pl
