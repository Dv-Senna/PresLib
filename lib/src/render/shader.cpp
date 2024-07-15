#include "pl/render/shader.hpp"

#include <fstream>
#include <map>
#include <stdexcept>
#include <vector>

#include <glad/gl.h>

#include "pl/config.hpp"
#include "pl/utils/files.hpp"



namespace pl::render {
	Shader::Shader(const pl::render::Shader::CreateInfos &createInfos) :
		m_stage {createInfos.stage},
		m_hash {0},
		m_shader {0}
	{
		const std::map<pl::render::ShaderStage, GLenum> shaderStageMap {
			{pl::render::ShaderStage::eVertex,   GL_VERTEX_SHADER},
			{pl::render::ShaderStage::eFragment, GL_FRAGMENT_SHADER}
		};

		std::vector<pl::Byte> hashData {};
		hashData.resize(sizeof(pl::render::ShaderStage) + createInfos.path.size() + createInfos.entryPoint.size());
		memcpy(hashData.data(), &m_stage, sizeof(pl::render::ShaderStage));
		memcpy(hashData.data() + sizeof(pl::render::ShaderStage), createInfos.path.data(), createInfos.path.size());
		memcpy(
			hashData.data() + sizeof(pl::render::ShaderStage) + createInfos.path.size(),
			createInfos.entryPoint.data(), createInfos.entryPoint.size()
		);
		m_hash = pl::utils::hash(hashData);

		auto it {s_loadedShaders.find(m_hash)};
		if (it != s_loadedShaders.end()) {
			m_shader = it->second;
			++s_loadedShaderCounts[m_hash];
			return;
		}



		std::string shaderPath {pl::Config::getShaderFolderPath() + createInfos.path + ".spv"};
		std::ifstream shaderFile {shaderPath, std::ios::binary};
		std::vector<pl::Byte> shaderData {pl::utils::readBinaryFile(shaderFile)};

		m_shader = glCreateShader(shaderStageMap.find(m_stage)->second);
		glShaderBinary(1, &m_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderData.data(), sizeof(pl::Byte) * shaderData.size());
		glSpecializeShader(m_shader, "main", 0, nullptr, nullptr);

		int compileStatus {};
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compileStatus);
		if (!compileStatus) {
			int infoLogLength {};
			glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::string log {};
			log.resize(infoLogLength + 1);
			glGetShaderInfoLog(m_shader, infoLogLength, &infoLogLength, log.data());
			log[infoLogLength] = '\0';
			throw std::runtime_error("Can't specialize spir-v shader : " + log);
		}

		s_loadedShaders[m_hash] = m_shader;
		s_loadedShaderCounts[m_hash] = 0;
	}


	Shader::~Shader() {
		if (m_shader == 0)
			return;

		pl::Count instanceCount {--s_loadedShaderCounts[m_hash]};
		if (instanceCount != 0)
			return;

		glDeleteShader(s_loadedShaders[m_hash]);
		s_loadedShaders.erase(m_hash);
		s_loadedShaderCounts.erase(m_hash);
	}


	bool Shader::operator==(const pl::render::Shader &shader) {
		return m_hash == shader.m_hash;
	}


	std::map<pl::Hash, pl::Uint32> Shader::s_loadedShaders {};
	std::map<pl::Hash, pl::Count> Shader::s_loadedShaderCounts {};

} // namespace pl::render
