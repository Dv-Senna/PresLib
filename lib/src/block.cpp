#include "block.hpp"



namespace pl
{
	Block::Block(pl::Instance &instance) :
		m_instance {instance},
		m_children {},
		m_id {s_id()}
	{

	}



	void Block::render()
	{
		for (auto children : m_children)
			children->render();
	}



	void Block::addChildren(pl::Block *block)
	{
		m_children.push_back(block);
	}



	void Block::removeChildren(pl::Block *block)
	{
		m_children.remove(block);
	}



	pl::BlockID Block::s_id()
	{
		static pl::BlockID id {0};
		return id++;
	}




} // namespace pl
