#pragma once

#include <map>
#include <vector>

#include "pl/core.hpp"
#include "pl/render/shader.hpp"
#include "pl/types.hpp"
#include "pl/utils/hash.hpp"



namespace pl::render {
	class PL_CORE Pipeline final {
		public:
			struct State {
				bool faceCulling;
				std::vector<pl::render::Shader*> shaders;
			};

			struct CreateInfos {
				pl::render::Pipeline::State state;
			};

			Pipeline(const pl::render::Pipeline::CreateInfos &createInfos);
			~Pipeline();

			bool operator==(const pl::render::Pipeline &pipeline) const noexcept;

			void use();
			void useFrom(const pl::render::Pipeline *oldPipeline);

			inline const pl::Uint32 &getProgram() const noexcept {return m_program;}
			inline const pl::render::Pipeline::State &getState() const noexcept {return m_state;}

		private:
			static std::map<pl::Hash, pl::Uint32> s_loadedPipelines;
			static std::map<pl::Hash, pl::Count> s_loadedPipelineCounts;

			pl::render::Pipeline::State m_state;
			pl::Uint32 m_program;
			pl::Hash m_hash;
	};

} // namespace pl::render
