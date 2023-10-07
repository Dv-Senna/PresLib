#pragma once

#include "../../manager/event.hpp"


namespace pl::impl::SDL2_renderer::manager
{
	class Event final : public pl::impl::manager::Event
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Event);

			Event() = default;
			~Event() override = default;


		private:
			bool m_handleEvent() override;
	};



} // namespace pl::impl::SDL2_renderer::manager
