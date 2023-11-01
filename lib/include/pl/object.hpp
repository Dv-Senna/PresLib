#pragma once

#include <memory>

#include "utils/id.hpp"
#include "utils/objectType.hpp"


namespace pl
{
	struct Object
	{
		pl::utils::ObjectType type;
		std::shared_ptr<void> data;
		pl::utils::Id id;
	};

} // namespace pl
