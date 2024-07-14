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
			};

			Shader(const pl::render::Shader::CreateInfos &createInfos);
			~Shader();

			bool operator==(const pl::render::Shader &shader);


		private:
			pl::render::ShaderStage m_stage;
			pl::Hash m_hash;
			pl::Uint32 m_shader;
	};

} // namespace pl::render
