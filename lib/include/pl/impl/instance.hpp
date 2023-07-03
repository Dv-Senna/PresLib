#pragma once

#include <any>
#include <functional>
#include <list>

#include <SDL2/SDL.h>

#include "../macros.inl"
#include "../utils/windowInfos.hpp"


namespace pl
{
	class Slide;
}


namespace pl::impl
{
	class Block;

	class Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			using RenderingCallback = std::function<void(const pl::impl::Instance *instance)>;

			inline Instance();
			inline virtual ~Instance() = default;

			virtual void run() = 0;
			virtual inline std::any getHandler() const noexcept = 0;

			inline void setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept;

			inline std::any getWindow() const noexcept;
			inline const pl::utils::WindowInfos &getWindowInfos() const noexcept;

			inline void addSlide(pl::Slide *slide);


		protected:
			inline void m_initSDL2();
			inline void m_quitSDL2();
			bool m_handleEvent();
			void m_render();

			std::any m_window;
			pl::utils::WindowInfos m_windowInfos;
			pl::impl::Instance::RenderingCallback m_renderingCallback;
			std::list<pl::Slide *> m_slides;
			std::list<pl::Slide *>::iterator m_currentSlide;
	};
} // namespace pl::impl


#include "instance.inl"