#pragma once

#include "../macros.inl"
#include "../graphicsApi.inl"
#include "../impl/manager/event.hpp"



namespace pl::manager
{
	template <pl::GraphicsApi API>
	class Event final
	{
		public:
			PL_TEMPLATE_CLASS_NO_COPY_MOVE(Event, API);

			Event();
			~Event();

			inline bool process();

			inline pl::impl::manager::Event *getImplementation() const;
			inline const std::array<pl::utils::KeyState, PL_KEYS_COUNT> &getKeys() const;


		private:
			pl::impl::manager::Event *m_impl;
	};



} // namespace pl::manager


#include "event.inl"