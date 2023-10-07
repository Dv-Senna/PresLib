#pragma once

#include <any>
#include <string>

#include "../macros.inl"
#include "manager.hpp"


namespace pl::impl
{
	class Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance(const std::string &title, pl::impl::Manager *manager);
			virtual ~Instance() = default;

			virtual void run() = 0;

			virtual const std::any &getHandler() const noexcept = 0;

			inline const std::string &getTitle() const noexcept;
			inline const pl::impl::Manager *getManager() const noexcept;

		
		protected:
			std::string m_title;
			pl::impl::Manager *m_manager;
	};


} // namespace pl::impl


#include "instance.inl"