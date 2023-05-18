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

	class Block
	{
		public:
			Block(pl::Instance &instance);
			virtual ~Block() = default;

			virtual void render();

			virtual void addChildren(pl::Block *block);
			virtual void removeChildren(pl::Block *block);

		
		protected:
			pl::Instance &m_instance;

		private:
			std::list<pl::Block *> m_children;
			pl::BlockID m_id;

			static pl::BlockID s_id();
	};

} // namespace pl
