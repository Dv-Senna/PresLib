#include "impl/instance.hpp"



namespace pl::impl
{
	Instance::Instance(const std::string &title, pl::impl::manager::Event *eventManager) :
		m_title {std::move(title)},
		m_eventManager {eventManager}
	{

	}



} // namespace pl::impl
