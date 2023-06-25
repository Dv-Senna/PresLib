#pragma once

#include <list>

#include "impl/block.hpp"
#include "instance.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Block
	{
		public:
			inline Block();
			virtual ~Block();

			inline void render();
			inline void addChild(pl::Block<API> *child);

			inline pl::impl::Block *getImplementation() const noexcept;


		protected:
			pl::impl::Block *m_impl;
		
		private:
			std::list<pl::Block<API> *> m_children;
	};

} // namespace pl



#include "block.inl"