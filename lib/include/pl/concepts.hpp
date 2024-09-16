#pragma once


#ifndef PL_APPLE

#include <concepts>

#include "pl/block.hpp"

#define PL_REQUIRES(...) requires __VA_ARGS__


namespace pl::concepts {
	template <typename T>
	concept IsBlock = requires(typename T::CreateInfos createInfos) {
		T(createInfos);
	} && std::is_base_of_v<pl::Block, T>;

} // namespace pl::concepts



#else
	#define PL_REQUIRES(...)
#endif