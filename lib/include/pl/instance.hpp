#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

#include "math/vec2.hpp"
#include "colorManager.hpp"
#include "fontManager.hpp"
#include "shaderManager.hpp"

#include "defines.inl"


namespace pl
{
	class Slide;
	class Block;

	/// @brief Main instance of PL. Should be load only once
	class Instance
	{
		public:
			using RenderingCallback = std::function<void(pl::Instance *instance)>;

			Instance();
			~Instance();

			void run();

			inline SDL_Window *getWindow() const noexcept {return m_window;}
			inline pl::FontManager &getFonts() noexcept {return *m_fontManager;}
			inline pl::ColorManager &getColors() noexcept {return m_colorManager;}
			inline pl::ShaderManager &getShaders() noexcept {return *m_shaderManager;}

			void addSlide(pl::Slide *slide);

			/// @brief Set a custom rendering callback. Called after slide rendering and right before SDL_RenderPresent(...)
			/// @param renderingCallback The callback. Take a pointer to the instance and return nothing
			void setCustomRenderingCallback(pl::Instance::RenderingCallback renderingCallback);
			/// @brief Set a custom background that would be shared by each slides. You can customise one specific slide by drawing on the whole screen or remove the shared background with flag pl::SlideFlag::no_background
			/// @param background The new shared background
			void setSharedBackground(pl::Block *background);
			/// @brief Set a custom overlay that would be shared by each slides. Add flag pl::SlideFlag::no_overlay to remove it on one specific slide.
			/// @param overlay The shared overlay
			void setSharedOverlay(pl::Block *overlay);
			void setTitlePosition(const pl::math::Vec2 &position);
			void setTitleFontSize(int fontSize);

			inline const pl::math::Vec2 &getTitlePosition() const noexcept {return m_titlePosition;}
			inline int getTitleFontSize() const noexcept {return m_titleFontSize;}


		private:
			SDL_Window *m_window;
			SDL_GLContext m_openglContext;
			pl::FontManager *m_fontManager;
			pl::ColorManager m_colorManager;
			pl::ShaderManager *m_shaderManager;
			std::vector<pl::Slide*> m_slides;
			uint32_t m_currentSlide;
			pl::Block *m_background, *m_overlay;
			pl::math::Vec2 m_titlePosition;
			int m_titleFontSize;
			pl::Instance::RenderingCallback m_renderingCallback;
	};

} // namespace pl
