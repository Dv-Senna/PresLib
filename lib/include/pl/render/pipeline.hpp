#pragma once

#include "pl/core.hpp"



namespace pl::render {
	enum class PipelineNodeType {
		eVerticesInput,
		eTextureInput,
		eTextureOutput
	};

	class PL_CORE Pipeline final {
		public:
			struct CreateInfos {

			};

			Pipeline(const pl::render::Pipeline::CreateInfos &createInfos);
			~Pipeline();
	};

} // namespace pl::render
