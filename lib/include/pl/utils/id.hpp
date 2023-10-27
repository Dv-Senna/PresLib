#pragma once

#include <cinttypes>


namespace pl::utils
{
	using Id = uint32_t;

	enum class IdType
	{
		internal = 0,
		external,
		
		__last
	};

	pl::utils::Id generateNewID(pl::utils::IdType type);

} // namespace pl::utils
