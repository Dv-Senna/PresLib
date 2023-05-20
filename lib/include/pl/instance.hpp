#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

#include "fontManager.hpp"
#include "slide.hpp"

#include "defines.inl"


namespace pl
{
	/// @brief Main instance of PL. Should be load only once
	class Instance
	{
		public:
			using RenderingCallback = std::function<void(pl::Instance *instance)>;

			Instance();
			~Instance();

			void run();

			inline SDL_Window *getWindow() const noexcept {return m_window;}
			inline SDL_Renderer *getRenderer() const noexcept {return m_renderer;}
			inline pl::FontManager &getFonts() noexcept {return *m_fontManager;}

			void addSlide(pl::Slide *slide);

			/// @brief Set a custom rendering callback. Called after slide rendering and right before SDL_RenderPresent(...)
			/// @param renderingCallback The callback. Take a pointer to the instance and return nothing
			void setCustomRenderingCallback(pl::Instance::RenderingCallback renderingCallback);


		private:
			SDL_Window *m_window;
			SDL_Renderer *m_renderer;
			pl::FontManager *m_fontManager;
			std::vector<pl::Slide*> m_slides;
			uint32_t m_currentSlide;
			pl::Instance::RenderingCallback m_renderingCallback;
	};

} // namespace pl
