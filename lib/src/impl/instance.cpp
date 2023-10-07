#include "impl/instance.hpp"



namespace pl::impl
{
	Instance::Instance(const std::string &title, pl::impl::Manager *manager) :
		m_title {std::move(title)},
		m_manager {manager}
	{

	}



} // namespace pl::impl
