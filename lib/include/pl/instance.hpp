#pragma once

#include <string>

#include "graphicsApi.inl"
#include "impl/instance.hpp"
#include "macros.inl"
#include "manager/event.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Instance final
	{
		public:
			PL_TEMPLATE_CLASS_NO_COPY_MOVE(Instance, API);

			Instance(const std::string &title);
			~Instance();

			inline void run();

			inline pl::impl::Instance *getImplementation() const;
			inline const std::any &getHandler() const;
			inline const std::string &getTitle() const;


		private:
			pl::impl::Instance *m_impl;
			pl::manager::Event<API> m_eventManager;
	};

} // namespace pl


#include "instance.inl"