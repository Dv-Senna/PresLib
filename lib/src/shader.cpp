#include <array>

#include "defines.inl"
#include "shader.hpp"
#include "utils/file.hpp"



namespace pl
{
	Shader::Shader(const std::string &path) : m_vertex {}, m_fragment {}, m_program {}
	{
		m_vertex = s_loadShader(path + ".vert", GL_VERTEX_SHADER);
		m_fragment = s_loadShader(path + ".frag", GL_FRAGMENT_SHADER);

		m_program = glCreateProgram();
		glAttachShader(m_program, m_vertex);
		glAttachShader(m_program, m_fragment);
		glLinkProgram(m_program);

		int success {};
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[PL_GL_INFO_LOG_MAX_LENGTH] {};
			glGetProgramInfoLog(m_program, PL_GL_INFO_LOG_MAX_LENGTH, nullptr, infoLog);
			throw std::runtime_error("PL : Can't link shaders to program : " + std::string(infoLog));
		}
	}



	Shader::~Shader()
	{
		glDeleteProgram(m_program);
		glDeleteShader(m_fragment);
		glDeleteShader(m_vertex);
	}



	void Shader::use()
	{
		glUseProgram(m_program);
	}



	void Shader::unuse()
	{
		glUseProgram(0);
	}



	void Shader::sendData(const std::string &name, float data)
	{
		glUniform1f(glGetAttribLocation(m_program, name.c_str()), data);
	}



	void Shader::sendData(const std::string &name, const pl::math::Vec2 &data)
	{
		glUniform2f(glGetAttribLocation(m_program, name.c_str()), data.x, data.y);
	}



	GLuint Shader::s_loadShader(const std::string &path, GLenum type)
	{
		std::ifstream file {pl::utils::loadReadFile(std::string(PL_DEFAULT_SHADER_FOLDER) + "/" + path)};
		std::array<const char*, 1> content {pl::utils::readContentFromFile(file).c_str()};

		GLuint shader {glCreateShader(type)};
		glShaderSource(shader, 1, content.data(), nullptr);
		glCompileShader(shader);

		int success {};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[PL_GL_INFO_LOG_MAX_LENGTH] {};
			glGetShaderInfoLog(shader, PL_GL_INFO_LOG_MAX_LENGTH, nullptr, infoLog);
			throw std::runtime_error("PL : Can't compile shader '" + path + "' : " + std::string(infoLog));
		}

		return shader;
	}



} // namespace pl
