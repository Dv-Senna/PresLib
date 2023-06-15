#pragma once

#include <string>

#include <GL/glew.h>

#include "../math/mat2.hpp"
#include "../math/vec2.hpp"
#include "../utils/color.hpp"


namespace pl::opengl
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
			void sendData(const std::string &name, const pl::math::Mat2 &data);
			void sendData(const std::string &name, const pl::utils::Color &color);

		
		private:
			static GLuint s_loadShader(const std::string &path, GLenum type);

			GLuint m_vertex, m_fragment, m_program;
	};

} // namespace pl
