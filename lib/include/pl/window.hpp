#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl {
	class PL_CORE Window final {
		public:
			struct CreateInfos {
				std::string title;
				pl::Vec2i size;
			};

			Window(const pl::Window::CreateInfos &createInfos);
			~Window();

			void handleResize();
			void setFullscreen(bool fullscreen);

			inline const pl::Vec2i &getSize() const noexcept {return m_size;}


		private:
			SDL_Window *m_window;
			SDL_GLContext m_context;
			pl::Vec2i m_size;
	};

} // namespace pl
