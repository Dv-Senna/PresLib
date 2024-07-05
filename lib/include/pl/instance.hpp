#pragma once

#include <string>

#include "pl/core.hpp"



namespace pl {
	struct InstanceCreateInfos {
		std::string presentationName;
	};

	class PL_CORE Instance final {
		public:
			Instance(const pl::InstanceCreateInfos &createInfos);
			~Instance();
	};

} // namespace pl
