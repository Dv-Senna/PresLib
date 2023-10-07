#include "manager.hpp"



namespace pl
{
	template <pl::GraphicsApi API>
	Manager<API>::Manager() : 
		m_event {},
		m_impl {
			m_event.getImplementation()
		}
	{

	}



	template <pl::GraphicsApi API>
	inline pl::impl::Manager *Manager<API>::getImplementation() noexcept
	{
		return &m_impl;
	}



	template <pl::GraphicsApi API>
	inline pl::manager::Event<API> &Manager<API>::getEvent() noexcept
	{
		return m_event;
	}



} // namespace pl
