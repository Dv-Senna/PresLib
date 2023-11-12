#pragma once

#include <SDL3/SDL.h>
#include <vulkan/vulkan.hpp>

#include "instance.hpp"



namespace pl::impl::vulkan
{
	class Surface final
	{
		public:
			Surface(pl::impl::vulkan::Instance &instance, SDL_Window *window);
			~Surface();

			vk::SurfaceKHR getSurface() const noexcept;

			bool isComplet() const noexcept;


		private:
			pl::impl::vulkan::Instance &m_instance;
			vk::SurfaceKHR m_surface;
	};

} // namespace pl::impl::vulkan
