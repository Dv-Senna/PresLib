#pragma once

#include <string>

#include "graphicsApi.inl"
#include "impl/instance.hpp"
#include "macros.inl"
#include "manager.hpp"


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
			inline const pl::Manager<API> &getManager() const noexcept;


		private:
			pl::impl::Instance *m_impl;
			pl::Manager<API> m_manager;
	};

} // namespace pl


#include "instance.inl"