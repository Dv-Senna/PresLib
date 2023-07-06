#include <iostream>

#include "block.hpp"
#include "slide.hpp"



namespace pl
{
	void Slide::render()
	{
		for (pl::impl::Block *block : m_blocks)
		{
			if (block != nullptr)
				block->render();

			#ifndef NDEBUG

				else
					std::cout << "PL : Warning : one of the rendered block doesn't exists (null pointer given)" << std::endl;

			#endif
		}
	}
} // namespace pl
