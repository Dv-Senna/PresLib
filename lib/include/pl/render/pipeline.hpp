#pragma once

#include "pl/core.hpp"
#include "pl/flow.hpp"



namespace pl::render {
	enum class PipelineNodeType {
		eVerticesInput,
		eTextureInput,
		eTextureOutput
	};

	struct PipelineNode : public pl::Node {
		pl::render::PipelineNodeType type;
	};

	class PL_CORE Pipeline final {
		public:
			struct CreateInfos {
				pl::Flow flow;
			};

			Pipeline(const pl::render::Pipeline::CreateInfos &createInfos);
			~Pipeline();
	};

} // namespace pl::render
