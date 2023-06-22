#pragma once

#include <any>
#include <functional>

#include <SDL2/SDL.h>

#include "../macros.inl"
#include "../utils/windowInfos.hpp"


namespace pl::impl
{
	class Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			using RenderingCallback = std::function<void(const pl::impl::Instance *instance)>;

			inline Instance();
			inline virtual ~Instance();

			virtual void run() = 0;
			virtual inline std::any getHandler() const noexcept = 0;

			inline void setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept;

			inline SDL_Window *getWindow() const noexcept;
			inline const pl::utils::WindowInfos &getWindowInfos() const noexcept;


		protected:
			inline void m_createWindow();

			SDL_Window *m_window;
			pl::utils::WindowInfos m_windowInfos;
			pl::impl::Instance::RenderingCallback m_renderingCallback;
	};
} // namespace pl::impl


#include "instance.inl"