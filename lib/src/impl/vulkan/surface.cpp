#include <SDL3/SDL_vulkan.h>

#include "impl/vulkan/surface.hpp"



namespace pl::impl::vulkan
{
	Surface::Surface(pl::impl::vulkan::Instance &instance, SDL_Window *window) : 
		m_instance {instance},
		m_surface {}
	{
		VkSurfaceKHR surface {};
		if (!SDL_Vulkan_CreateSurface(window, m_instance.getInstance(), &surface))
			throw std::runtime_error("PL : Vulkan can't create an SDL3 vulkan surface : " + std::string(SDL_GetError()));

		m_surface = surface;
	}



	Surface::~Surface()
	{
		vkDestroySurfaceKHR(m_instance.getInstance(), m_surface, nullptr);
	}



	vk::SurfaceKHR Surface::getSurface() const noexcept
	{
		return m_surface;
	}



	bool Surface::isComplet() const noexcept
	{
		return m_surface != vk::SurfaceKHR();
	}



} // namespace pl::impl::vulkan
