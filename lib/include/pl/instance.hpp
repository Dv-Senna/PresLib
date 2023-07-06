#pragma once

#include "fontManager.hpp"
#include "graphicsApi.inl"
#include "impl/instance.hpp"
#include "slide.hpp"
#include "theme.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Block;
	

	/// @brief The class that handle the life-cycle of the whole library
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Instance final
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance();
			~Instance();

			/// @brief Run the program main loop. All wanted slides and blocks must have been created before this call and destroyed after
			inline void run();
			/// @brief Get a handler specific to the pl::GraphicsApi used
			/// @return The handler used by the graphics api
			inline std::any getHandler() const noexcept;

			/// @brief Add a custom rendering callback where you can make custom things. Call right before refreshing the screen
			/// @param callback The custom rendering callback
			inline void setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept;

			inline std::any getWindow() const noexcept;
			inline const pl::utils::WindowInfos &getWindowInfos() const noexcept;
			inline pl::impl::Instance *getImplementation() const noexcept;
			inline pl::FontManager &getFonts() noexcept;
			inline const pl::Theme &getTheme() const noexcept;

			/// @brief Register a new slide to the instance. Slides's order is the registration order
			/// @param slide The slide to register
			inline void addSlide(pl::Slide *slide);
			/// @brief Set the current theme. Know that if you created blocks before this call, they would still use the colors, fonts, ..., of the previously loaded theme
			/// @param theme The new theme to load
			inline void setTheme(const pl::Theme &theme);


		private:
			pl::impl::Instance *m_impl;
	};

} // namespace pl


#include "instance.inl"