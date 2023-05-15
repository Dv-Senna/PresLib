#pragma once

#include <cinttypes>
#include <list>

#include "instance.hpp"


namespace pl
{
	using BlockID = uint32_t;

	class Block
	{
		public:
			Block(pl::Instance &instance);
			virtual ~Block() = default;

			virtual void render();

			void addChildren(pl::Block *block);
			void removeChildren(pl::Block *block);

		
		private:
			pl::Instance &m_instance;
			std::list<pl::Block *> m_children;
			pl::BlockID m_id;

			static pl::BlockID s_id();
	};

} // namespace pl
