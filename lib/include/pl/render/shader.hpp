#pragma once

#include <string>

#include "pl/core.hpp"
#include "pl/utils/hash.hpp"



namespace pl::render {
	enum class ShaderStage {
		eVertex,
		eFragment
	};

	class PL_CORE Shader final {
		public:
			struct CreateInfos {
				pl::render::ShaderStage stage;
				std::string path;
				std::string entryPoint;
			};

			Shader(const pl::render::Shader::CreateInfos &createInfos);
			~Shader();

			bool operator==(const pl::render::Shader &shader);


		private:
			static std::map<pl::Hash, pl::Uint32> s_loadedShaders;
			static std::map<pl::Hash, pl::Count> s_loadedShaderCounts;

			pl::render::ShaderStage m_stage;
			pl::Hash m_hash;
			pl::Uint32 m_shader;
	};

} // namespace pl::render
