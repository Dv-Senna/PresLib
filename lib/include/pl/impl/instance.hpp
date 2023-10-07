#pragma once

#include <any>
#include <string>

#include "../macros.inl"
#include "manager/event.hpp"


namespace pl::impl
{
	class Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance(const std::string &title, pl::impl::manager::Event *eventManager);
			virtual ~Instance() = default;

			virtual void run() = 0;

			virtual const std::any &getHandler() const noexcept = 0;

			inline const std::string &getTitle() const noexcept;
			inline const pl::impl::manager::Event *getEventManager() const noexcept;

		
		protected:
			std::string m_title;
			pl::impl::manager::Event *m_eventManager;
	};


} // namespace pl::impl


#include "instance.inl"