#pragma once


#ifndef PL_APPLE

#include <concepts>

#include "pl/component.hpp"

#define PL_REQUIRES(...) requires __VA_ARGS__


namespace pl::concepts {
	template <typename T>
	concept IsComponent = requires(typename T::CreateInfos createInfos) {
		T(createInfos);
	} && std::is_base_of_v<pl::Component, T>;

} // namespace pl::concepts



#else
	#define PL_REQUIRES(...)
#endif