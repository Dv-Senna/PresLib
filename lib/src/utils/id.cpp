#include <array>
#include <stdexcept>

#include "utils/id.hpp"



namespace pl::utils
{
	pl::utils::Id generateNewID(pl::utils::IdType type)
	{
		static std::array<pl::utils::Id, static_cast<size_t> (pl::utils::IdType::__last)> currentIDs {1, 1};
		if (type >= pl::utils::IdType::__last)
			throw std::runtime_error("PL : Invalid id type given. Unable to generate new id");

		return currentIDs[static_cast<size_t> (type)]++;
	}
	
} // namespace pl::utils
