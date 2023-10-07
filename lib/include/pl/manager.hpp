#pragma once

#include "graphicsApi.inl"
#include "impl/manager.hpp"
#include "macros.inl"
#include "manager/event.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Manager final
	{
		public:
			PL_TEMPLATE_CLASS_NO_COPY_MOVE(Manager, API);

			Manager();
			~Manager() = default;

			inline pl::impl::Manager *getImplementation() noexcept;
			inline pl::manager::Event<API> &getEvent() noexcept;


		private:
			pl::manager::Event<API> m_event;
			pl::impl::Manager m_impl;
	};



} // namespace pl


#include "manager.inl"