#pragma once

#include "../block.hpp"


namespace pl::block
{
	/// @brief A block that is made to be use as a node, as a parent
	class Group final : public pl::Block
	{
		public:
			Group(pl::Instance &instance);
			~Group() = default;
	};

} // namespace pl::block
