#pragma once

#include <list>

#include "instance.hpp"


namespace pl::impl
{
	class Block
	{
		public:
			inline Block(pl::impl::Instance *instance);
			virtual ~Block() = default;

			virtual void render() = 0;

			inline void addChild(pl::impl::Block *block);

		protected:
			inline void m_renderChildren();
			
			pl::impl::Instance *m_instance;

		private:
			std::list<pl::impl::Block *> m_children;
	};

} // namespace pl::impl


#include "block.inl"