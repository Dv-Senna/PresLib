#include "slide.hpp"



namespace pl::manager
{
	template <pl::GraphicsApi API>
	Slide<API>::Slide() : 
		m_impl {}
	{

	}



	template <pl::GraphicsApi API>
	void Slide<API>::add(pl::Slide<API> *slide)
	{
		m_impl.add(slide->getImplementation())
	}



	template <pl::GraphicsApi API>
	void Slide<API>::draw()
	{
		m_impl.add();
	}



	template <pl::GraphicsApi API>
	bool Slide<API>::process(pl::manager::Event<API> &eventManager)
	{
		return m_impl.process(eventManager.getImplementation());
	}



	template <pl::GraphicsApi API>
	pl::impl::manager::Slide *Slide<API>::getImplementation() noexcept
	{
		return &m_impl;
	}



} // namespace pl::manager
