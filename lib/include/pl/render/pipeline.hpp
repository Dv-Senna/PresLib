#pragma once

#include <vector>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::render {
	class PL_CORE Pipeline final {
		public:
			struct State {
				bool faceCulling;
				//std::vector<>;
			};

			struct CreateInfos {
				pl::render::Pipeline::State state;
			};

			Pipeline();
			~Pipeline();
	};

} // namespace pl::render
