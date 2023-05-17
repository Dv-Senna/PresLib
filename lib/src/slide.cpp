#include "block.hpp"
#include "slide.hpp"



namespace pl
{
	Slide::Slide() : m_blocks {}
	{

	}



	void Slide::render()
	{
		for (auto block : m_blocks)
			block->render();
	}



	void Slide::addChildren(pl::Block *block)
	{
		m_blocks.push_back(block);
	}



	void Slide::removeChildren(pl::Block *block)
	{
		m_blocks.remove(block);
	}





} // namespace pl
