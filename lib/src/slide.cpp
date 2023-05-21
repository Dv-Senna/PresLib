#include "block.hpp"
#include "slide.hpp"



namespace pl
{
	Slide::Slide(pl::SlideFlag flags) : m_flags {flags}, m_blocks {}
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
