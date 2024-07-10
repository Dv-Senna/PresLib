#pragma once

#include "pl/core.hpp"



namespace pl::render {
	struct PipelineStage {

	};

	class PL_CORE Pipeline final {
		public:
			struct CreateInfos {

			};

			Pipeline(const pl::render::Pipeline::CreateInfos &createInfos);
			~Pipeline();
	};

} // namespace pl::render
