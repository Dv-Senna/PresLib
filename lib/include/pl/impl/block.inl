#pragma once

#include "block.hpp"


namespace pl::impl
{
	Block::Block(pl::impl::Instance *instance) : m_instance {instance}, m_children {}
	{

	}



	void Block::addChild(pl::impl::Block *block)
	{
		m_children.push_back(block);
	}



	void Block::m_renderChildren()
	{
		for (auto child : m_children)
			child->render();
	}



} // namespace pl::impl
