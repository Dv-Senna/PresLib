#include "slide.hpp"



namespace pl
{
	template <pl::GraphicsApi API>
	Slide<API>::Slide(pl::Instance<API> &instance) : 
		m_impl {instance.getImplementation()},
		m_instance {instance}
	{

	}



	template <pl::GraphicsApi API>
	inline void Slide<API>::draw()
	{
		m_impl.draw();
	}



	template <pl::GraphicsApi API>
	pl::impl::Slide *Slide<API>::getImplementation() noexcept
	{
		return &m_impl;
	}



	template <pl::GraphicsApi API>
	pl::Instance<API> &Slide<API>::getInstance() noexcept
	{
		return m_instance;
	}



} // namespace pl
