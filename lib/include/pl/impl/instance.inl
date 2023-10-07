#include "instance.hpp"



namespace pl::impl
{
	const std::string &Instance::getTitle() const noexcept
	{
		return m_title;
	}



	const pl::impl::manager::Event *Instance::getEventManager() const noexcept
	{
		return m_eventManager;
	}



} // namespace pl::impl
