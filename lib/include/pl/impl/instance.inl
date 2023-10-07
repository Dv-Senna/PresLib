#include "instance.hpp"



namespace pl::impl
{
	const std::string &Instance::getTitle() const noexcept
	{
		return m_title;
	}



	const pl::impl::Manager *Instance::getManager() const noexcept
	{
		return m_manager;
	}



} // namespace pl::impl
