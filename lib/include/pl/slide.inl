#include "slide.hpp"



namespace pl
{
	template <pl::GraphicsApi API>
	Slide::Slide(pl::Instance<API> &instance, pl::SlideFlags flags) : m_blocks {}, m_flags {flags}
	{
		instance.addSlide(this);
	}



	template <pl::GraphicsApi API>
	void Slide::addBlock(pl::Block<API> *block)
	{
		m_blocks.push_back(block->getImplementation());
	}



	pl::SlideFlags Slide::getFlags() const noexcept
	{
		return m_flags;
	}



	const std::list<pl::impl::Block*> &Slide::getBlocks() const noexcept
	{
		return m_blocks;
	}



} // namespace 
