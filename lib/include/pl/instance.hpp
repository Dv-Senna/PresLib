#pragma once

#include <SDL2/SDL.h>


#define PL_DEFAULT_VIEWPORT_WIDTH 1920
#define PL_DEFAULT_VIEWPORT_HEIGHT 1080


namespace pl
{
	class Instance
	{
		public:
			Instance();
			~Instance();

			void run();


		private:
			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
	};

} // namespace pl
