#pragma once

#include "../block.hpp"
#include "../impl/group.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Group final : public pl::Block<API>
	{
		public:
			Group(pl::Instance<API> &instance) : pl::Block<API> ()
			{
				this->m_impl = new pl::impl::Group(instance.getImplementation());
			}

			~Group() = default;
	};

} // namespace pl::blocks
