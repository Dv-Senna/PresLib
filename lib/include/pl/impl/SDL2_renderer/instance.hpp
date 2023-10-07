#pragma once

#include <any>
#include <string>

#include "../instance.hpp"


namespace pl::impl::SDL2_renderer
{
	class Instance final : public pl::impl::Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance(const std::string &title, pl::impl::manager::Event *eventManager);
			~Instance() override;

			void run() override;

			inline const std::any &getWindow() const noexcept;
			const std::any &getHandler() const noexcept override;


		private:
			bool m_mainloop();

			/* `SDL_Window*` */ std::any m_window;
			/* `SDL_Renderer*` */ std::any m_renderer;
	};

} // namespace pl::impl::SDL2_renderer


#include "instance.inl"