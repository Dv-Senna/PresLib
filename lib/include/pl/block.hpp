#pragma once

#include <cinttypes>
#include <list>

#include "instance.hpp"


namespace pl
{
	using BlockID = uint32_t;

	enum class DrawingType
	{
		outlined, filled
	};

	/// @brief The base class of all blocks
	class Block
	{
		public:
			/// @brief Constructor
			/// @param instance A pointer to the instance of pl
			Block(pl::Instance &instance);
			virtual ~Block() = default;

			/// @brief Render the block and its children
			virtual void render();

			/// @brief Add a child block to the current block.
			/// @param block The block to add as child
			/// @warning Can contain assert depending on the implementation !
			virtual void addChildren(pl::Block *block);
			/// @brief Remove a child block to the current block
			/// @param block The block to remove as child
			/// @warning Can contain assert depending on the implementation !
			virtual void removeChildren(pl::Block *block);

		
		protected:
			pl::Instance &m_instance;

		private:
			std::list<pl::Block *> m_children;
			pl::BlockID m_id;

			static pl::BlockID s_id();
	};

} // namespace pl
