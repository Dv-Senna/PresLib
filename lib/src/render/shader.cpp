#include "pl/render/shader.hpp"

#include <map>
#include <vector>

#include <glad/gl.h>



namespace pl::render {
	Shader::Shader(const pl::render::Shader::CreateInfos &createInfos) :
		m_stage {createInfos.stage},
		m_hash {0},
		m_shader {0}
	{
		static const std::map<pl::render::ShaderStage, GLenum> shaderStageMap {
			{pl::render::ShaderStage::eVertex,   GL_VERTEX_SHADER},
			{pl::render::ShaderStage::eFragment, GL_FRAGMENT_SHADER}
		};

		std::vector<pl::Byte> hashData {};
		hashData.resize(sizeof(pl::render::ShaderStage) + createInfos.path.size());
		memcpy(hashData.data(), &m_stage, sizeof(pl::render::ShaderStage));
		memcpy(hashData.data() + sizeof(pl::render::ShaderStage), createInfos.path.data(), createInfos.path.size());
		m_hash = pl::utils::hash(hashData);

		m_shader = glCreateShader(shaderStageMap.find(m_stage)->second);

		GLint sourceLength;
		//glShaderSource(m_shader, 1, );
	}


	Shader::~Shader() {
		if (m_shader != 0)
			glDeleteShader(m_shader);
	}


	bool Shader::operator==(const pl::render::Shader &shader) {

	}


} // namespace pl::render
