#pragma once

#include <tuple>



namespace pl {
	enum class Result {
		eSuccess,
		eFailure
	};

	template <typename T>
	using Potential = std::tuple<T, pl::Result>;

} // namespace pl
