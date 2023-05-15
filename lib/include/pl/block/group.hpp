#pragma once

#include "../block.hpp"


namespace pl::block
{
	class Group final : public pl::Block
	{
		public:
			Group(pl::Instance &instance);
			~Group() = default;
	};

} // namespace pl::block
