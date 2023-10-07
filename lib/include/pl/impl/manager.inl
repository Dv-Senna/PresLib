#include "manager.hpp"



namespace pl::impl
{
	Manager::Manager(pl::impl::manager::Event *event) : 
		m_event {event}
	{

	}



	pl::impl::manager::Event *Manager::getEvent() const noexcept
	{
		return m_event;
	}



} // namespace pl::impl
