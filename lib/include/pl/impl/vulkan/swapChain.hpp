#pragma once

#include <SDL3/SDL.h>
#include <vulkan/vulkan.hpp>

#include "device.hpp"
#include "instance.hpp"
#include "surface.hpp"


namespace pl::impl::vulkan
{
	

	class SwapChain final
	{
		public:
			SwapChain(
				pl::impl::vulkan::Instance &instance,
				pl::impl::vulkan::Surface &surface,
				pl::impl::vulkan::Device &device,
				SDL_Window *window,
				pl::graphics::Efficency efficiency
			);
			~SwapChain();

			vk::SwapchainKHR getSwapChain() const noexcept;
			const std::vector<vk::Image> &getImages() const noexcept;
			vk::Format getFormat() const noexcept;
			vk::Extent2D getExtent() const noexcept;

			bool isComplet() const noexcept;


		private:
			void m_load();
			void m_unload();

			vk::SurfaceFormat2KHR s_chooseFormats(const std::vector<vk::SurfaceFormat2KHR> &formats);
			vk::PresentModeKHR s_choosePresentMode(const std::vector<vk::PresentModeKHR> &presentModes, pl::graphics::Efficency efficiency);
			vk::Extent2D s_chooseExtent(const vk::SurfaceCapabilities2KHR &capabilities, SDL_Window *window);

			pl::impl::vulkan::Instance &m_instance;
			pl::impl::vulkan::Surface &m_surface;
			pl::impl::vulkan::Device &m_device;
			SDL_Window *m_window;
			vk::SwapchainKHR m_swapChain;
			pl::graphics::Efficency m_efficiency;
			std::vector<vk::Image> m_images;
			vk::Format m_format;
			vk::Extent2D m_extent;
	};

} // namespace pl::impl::vulkan
