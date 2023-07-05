#pragma once

#include "../block.hpp"
#include "../impl/group.hpp"


namespace pl::blocks
{
	/// @brief A block to create group of other blocks
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Group final : public pl::Block<API>
	{
		public:
			/// @brief A block to create group of other blocks
			/// @param instance The current instance of PresLib
			Group(pl::Instance<API> &instance) : pl::Block<API> ()
			{
				this->m_impl = new pl::impl::Group(instance.getImplementation());
			}

			~Group() = default;
	};

} // namespace pl::blocks
