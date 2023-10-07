#pragma once

#include <array>

#include "../../defines.inl"
#include "../../macros.inl"
#include "../../utils/keys.hpp"


namespace pl::impl::manager
{
	class Event
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Event);

			Event();
			virtual ~Event() = default;

			bool process();
			inline const std::array<pl::utils::KeyState, PL_KEYS_COUNT> &getKeys() const noexcept;

		protected:
			virtual bool m_handleEvent() = 0;

			std::array<pl::utils::KeyState, PL_KEYS_COUNT> m_keys;
	};



} // namespace pl::impl::manager


#include "event.inl"