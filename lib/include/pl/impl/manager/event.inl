#include "event.hpp"



namespace pl::impl::manager
{
	const std::array<pl::utils::KeyState, PL_KEYS_COUNT> &Event::getKeys() const noexcept
	{
		return m_keys;
	}


	
} // namespace pl::impl::manager
