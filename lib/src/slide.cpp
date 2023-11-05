#include "slide.hpp"



namespace pl
{
	Slide::Slide(const pl::Slide::CreateInfo & /* createInfos */) : 
		m_blocks {}
	{
		
	}



	void Slide::draw(const glm::mat4 &globalTransformation)
	{
		for (auto &block : m_blocks)
		{
			block->draw(globalTransformation);
		}
	}



	void Slide::registerBlock(std::shared_ptr<pl::Block> block)
	{
		m_blocks.push_back(block);
	}



} // namespace pl
