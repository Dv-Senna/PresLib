#pragma once

#include <list>

#include <SDL2/SDL.h>

#include "slide.hpp"


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

			SDL_Window *getWindow() const noexcept;
			SDL_Renderer *getRenderer() const noexcept;

			void addSlide(pl::Slide *slide);
			void removeSlide(pl::Slide *slide);


		private:
			SDL_Window *m_window;
			SDL_Renderer *m_renderer;

			std::list<pl::Slide*> m_slides;
	};

} // namespace pl
