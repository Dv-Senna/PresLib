#pragma once

#include "instance.hpp"


namespace pl::impl
{
	class Block
	{
		public:
			inline Block(pl::impl::Instance *instance);
			virtual ~Block() = default;

			virtual void render() = 0;

		protected:
			pl::impl::Instance *m_instance;
	};

} // namespace pl::impl


#include "block.inl"