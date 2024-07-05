#pragma once

#include "pl/component.hpp"
#include "pl/concepts.hpp"
#include "pl/core.hpp"
#include "pl/reference.hpp"



namespace pl {
	class PL_CORE ComponentFactory final {
		public:
			ComponentFactory() = default;
			~ComponentFactory() = default;

			template <typename T>
			PL_REQUIRES(pl::concepts::IsComponent<T>)
			pl::Reference<T> create(const typename T::CreateInfos &createInfos);
	};

} // namespace pl
