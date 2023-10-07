#include <cinttypes>

#include "impl/manager/event.hpp"



namespace pl::impl::manager
{
	Event::Event() : 
		m_keys {}
	{
		for (size_t i {0}; i < PL_KEYS_COUNT; ++i)
			m_keys[i] = {false, false};
	}



	bool Event::process()
	{
		if (!this->m_handleEvent())
			return false;

		if (m_keys[pl::utils::keys::escape].isDown)
			return false;

		return true;
	}



} // namespace pl::impl::manager
