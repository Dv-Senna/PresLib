#include "block.hpp"
#include "slide.hpp"



namespace pl
{
	void Slide::render()
	{
		for (pl::impl::Block *block : m_blocks)
			block->render();
	}
} // namespace pl
