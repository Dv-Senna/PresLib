#pragma once

#include "pl/core.hpp"
#include "pl/types.hpp"


namespace pl {
	using Hash = pl::Uint64;
} // namespace pl

namespace pl::utils {
	template <typename T>
	PL_CORE pl::Hash hash(const T &value);

} // namespace pl::utils
