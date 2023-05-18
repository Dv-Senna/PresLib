#pragma once

#include <functional>
#include <list>

#include <SDL2/SDL.h>

#include "fontManager.hpp"
#include "slide.hpp"


#define PL_DEFAULT_VIEWPORT_WIDTH 1920
#define PL_DEFAULT_VIEWPORT_HEIGHT 1080


namespace pl
{
	class Instance
	{
		public:
			using RenderingCallback = std::function<void(pl::Instance *instance)>;

			Instance();
			~Instance();

			void run();

			inline SDL_Window *getWindow() const noexcept {return m_window;}
			inline SDL_Renderer *getRenderer() const noexcept {return m_renderer;}
			inline pl::FontManager &getFonts() noexcept {return m_fontManager;}

			void addSlide(pl::Slide *slide);
			void removeSlide(pl::Slide *slide);

			void setCustomRenderingCallback(pl::Instance::RenderingCallback renderingCallback);


		private:
			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
			pl::FontManager m_fontManager;
			std::list<pl::Slide*> m_slides;
			pl::Instance::RenderingCallback m_renderingCallback;
	};

} // namespace pl
