#include "pl/render/pipeline.hpp"

#include <glad/gl.h>



namespace pl::render {
	Pipeline::Pipeline(const pl::render::Pipeline::CreateInfos &createInfos) :
		m_state {createInfos.state},
		m_program {0},
		m_hash {0}
	{
		m_hash = pl::utils::hash(m_state);
		auto it {s_loadedPipelines.find(m_hash)};
		if (it != s_loadedPipelines.end()) {
			m_program = it->second;
			++s_loadedPipelineCounts[m_hash];
			return;
		}

		m_program = glCreateProgram();
		for (const auto &shader : m_state.shaders)
			glAttachShader(m_program, shader->getShader());
		glLinkProgram(m_program);

		pl::Int succeed;
		glGetProgramiv(m_program, GL_LINK_STATUS, &succeed);
		if (!succeed) {
			int infoLogLength {};
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::string log {};
			log.resize(infoLogLength + 1);
			glGetProgramInfoLog(m_program, infoLogLength, &infoLogLength, log.data());
			log[infoLogLength] = '\0';
			throw std::runtime_error("Can't link program : " + log);
		}
		
		s_loadedPipelines[m_hash] = m_program;
		s_loadedPipelineCounts[m_hash] = 1;
	}


	Pipeline::~Pipeline() {
		if (m_program == 0)
			return;

		pl::Count instanceCount {--s_loadedPipelineCounts[m_hash]};
		if (instanceCount != 0)
			return;

		glDeleteProgram(s_loadedPipelines[m_hash]);
		s_loadedPipelines.erase(m_hash);
		s_loadedPipelineCounts.erase(m_hash);
	}


	bool Pipeline::operator==(const pl::render::Pipeline &pipeline) const noexcept {
		return m_hash == pipeline.m_hash;
	}


	std::map<pl::Hash, pl::Uint32> Pipeline::s_loadedPipelines {};
	std::map<pl::Hash, pl::Count> Pipeline::s_loadedPipelineCounts {};

} // namespace pl::render
