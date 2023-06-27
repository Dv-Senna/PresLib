#pragma once

#include <list>

#include "graphicsApi.inl"


namespace pl
{
	template <pl::GraphicsApi API>
	class Instance;

	template <pl::GraphicsApi API>
	class Block;

	namespace impl
	{
		class Block;
	}


	class Slide final
	{
		public:
			template <pl::GraphicsApi API>
			Slide(pl::Instance<API> &instance);
			~Slide() = default;

			void render();

			template <pl::GraphicsApi API>
			void addBlock(pl::Block<API> *block);

		
		private:
			std::list<pl::impl::Block *> m_blocks;
	};

} // namespace pl


#include "slide.inl"