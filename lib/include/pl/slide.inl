#include "slide.hpp"



namespace pl
{
	template <pl::GraphicsApi API>
	Slide::Slide(pl::Instance<API> &instance) : m_blocks {}
	{
		instance.addSlide(this);
	}



	template <pl::GraphicsApi API>
	void Slide::addBlock(pl::Block<API> *block)
	{
		m_blocks.push_back(block->getImplementation());
	}



} // namespace 
