#pragma once

#include <string>

#include <GL/glew.h>

#include "math/vec2.hpp"


namespace pl
{
	class Shader final
	{
		public:
			Shader(const std::string &path);
			~Shader();

			void use();
			void unuse();

			void sendData(const std::string &name, float data);
			void sendData(const std::string &name, const pl::math::Vec2 &data);

		
		private:
			static GLuint s_loadShader(const std::string &path, GLenum type);

			GLuint m_vertex, m_fragment, m_program;
	};

} // namespace pl
