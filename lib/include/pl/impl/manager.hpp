#pragma once

#include "../macros.inl"
#include "manager/event.hpp"


namespace pl::impl
{
	class Manager
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Manager);

			inline Manager(pl::impl::manager::Event *event);
			~Manager() = default;

			inline pl::impl::manager::Event *getEvent() const noexcept;


		private:
			pl::impl::manager::Event *m_event;
	};

} // namespace pl::impl


#include "manager.inl"