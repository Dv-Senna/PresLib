#include "block.hpp"
#include "slide.hpp"



namespace pl
{
	Slide::Slide(pl::Instance &instance, pl::SlideFlag flags) : 
		m_instance {instance},
		m_flags {flags},
		m_blocks {},
		m_title {nullptr}
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



	void Slide::setTitle(const std::string &title)
	{
		m_title = std::make_unique<pl::block::Text> (
			m_instance,
			m_instance.getTitlePosition(),
			title,
			"title-font",
			m_instance.getTitleFontSize(),
			m_instance.getColors().getScheme().title
		);

		this->addChildren(m_title.get());
	}



} // namespace pl
