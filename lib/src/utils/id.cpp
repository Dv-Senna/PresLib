#include <array>
#include <stdexcept>

#include "utils/id.hpp"



namespace pl::utils
{
	pl::utils::Id generateNewID()
	{
		static size_t id {1};
		return id++;
	}
	
} // namespace pl::utils
