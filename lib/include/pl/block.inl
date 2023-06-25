#pragma once

#include "block.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	Block<API>::Block() : m_impl {nullptr}, m_children {}
	{

	}



	template <pl::GraphicsApi API>
	Block<API>::~Block()
	{
		if (m_impl != nullptr)
			delete m_impl;
	}



	template <pl::GraphicsApi API>
	void Block<API>::render()
	{
		for (auto child : m_children)
			child->render();

		if (m_impl != nullptr)
			m_impl->render();
	}



	template <pl::GraphicsApi API>
	void Block<API>::addChild(pl::Block<API> *child)
	{
		m_children.push_back(child);
	}



	template <pl::GraphicsApi API>
	pl::impl::Block *Block<API>::getImplementation() const noexcept
	{
		return m_impl;
	}



} // namespace pl
