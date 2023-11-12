#include <algorithm>
#include <limits>
#include <stdexcept>

#include "impl/vulkan/swapChain.hpp"



namespace pl::impl::vulkan
{
	SwapChain::SwapChain(
		pl::impl::vulkan::Instance &instance,
		pl::impl::vulkan::Surface &surface,
		pl::impl::vulkan::Device &device,
		SDL_Window *window,
		pl::graphics::Efficency efficiency
	) :
		m_instance {instance},
		m_surface {surface},
		m_device {device},
		m_window {window},
		m_swapChain {},
		m_efficiency {efficiency},
		m_images {},
		m_format {},
		m_extent {}
	{
		this->m_load();
	}



	SwapChain::~SwapChain()
	{
		this->m_unload();
	}



	vk::SwapchainKHR SwapChain::getSwapChain() const noexcept
	{
		return m_swapChain;
	}



	const std::vector<vk::Image> &SwapChain::getImages() const noexcept
	{
		return m_images;
	}



	vk::Format SwapChain::getFormat() const noexcept
	{
		return m_format;
	}



	vk::Extent2D SwapChain::getExtent() const noexcept
	{
		return m_extent;
	}



	bool SwapChain::isComplet() const noexcept
	{
		return m_swapChain != vk::SwapchainKHR() && !m_images.empty();
	}



	void SwapChain::m_load()
	{
		static bool firstLoad {true};

		const auto &swapChainSupportDetails {m_device.getPhysicalDevice().swapChainSupportDetails};

		auto format {pl::impl::vulkan::SwapChain::s_chooseFormats(swapChainSupportDetails.formats)};
		auto presentMode {pl::impl::vulkan::SwapChain::s_choosePresentMode(swapChainSupportDetails.presentModes, m_efficiency)};
		auto extent {pl::impl::vulkan::SwapChain::s_chooseExtent(swapChainSupportDetails.capabilities, m_window)};

		vk::SwapchainCreateInfoKHR createInfo {};
		createInfo.surface = m_surface.getSurface();
		createInfo.imageFormat = format.surfaceFormat.format;
		createInfo.imageColorSpace = format.surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment; // vk::ImageUsageFlagBits::eTransferDst
		createInfo.preTransform = swapChainSupportDetails.capabilities.surfaceCapabilities.currentTransform;
		createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		createInfo.presentMode = presentMode;
		createInfo.clipped = vk::True;

		createInfo.minImageCount = swapChainSupportDetails.capabilities.surfaceCapabilities.minImageCount + 1;
		if (swapChainSupportDetails.capabilities.surfaceCapabilities.maxImageCount != 0
			&& createInfo.minImageCount > swapChainSupportDetails.capabilities.surfaceCapabilities.maxImageCount)
			createInfo.minImageCount = swapChainSupportDetails.capabilities.surfaceCapabilities.maxImageCount;

		uint32_t graphicsIndex {}, presentIndex {};
		for (size_t i {0}; i < m_device.getPhysicalDevice().queueFamilies.rawProperties.size(); ++i)
		{
			const auto &queue {m_device.getPhysicalDevice().queueFamilies.rawProperties[i]};
			bool graphicsSupport {pl::impl::vulkan::isQueueSupportingFlag(
				m_device.getPhysicalDevice().device,
				m_surface.getSurface(),
				pl::impl::vulkan::QueueFlagBits::eGraphics,
				queue.queueFamilyProperties.queueFlags, i
			)};
			bool presentSupport {pl::impl::vulkan::isQueueSupportingFlag(
				m_device.getPhysicalDevice().device,
				m_surface.getSurface(),
				pl::impl::vulkan::QueueFlagBits::ePresentKHR,
				queue.queueFamilyProperties.queueFlags, i
			)};

			if (graphicsSupport)
				graphicsIndex = i;

			if (presentSupport)
				presentIndex = i;

			if (graphicsSupport && presentSupport)
				break;
		}

		uint32_t indices[2] {graphicsIndex, presentIndex};

		if (graphicsIndex == presentIndex)
			createInfo.imageSharingMode = vk::SharingMode::eExclusive;

		else
		{
			createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = indices;
		}

		if (!firstLoad)
			createInfo.oldSwapchain = m_swapChain;

		else
			firstLoad = false;

		m_swapChain = m_device.getDevice().createSwapchainKHR(createInfo, nullptr);

		m_instance.getLogStream() << "PL : Vulkan swap chain created\n" << std::endl;

		m_format = format.surfaceFormat.format;
		m_extent = extent;

		uint32_t count {};
		if (m_device.getDevice().getSwapchainImagesKHR(m_swapChain, &count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't retrieve swapchaine images count");

		m_images.resize(count);
		if (m_device.getDevice().getSwapchainImagesKHR(m_swapChain, &count, m_images.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't retrieve swapchaine images");
	}



	void SwapChain::m_unload()
	{
		m_device.getDevice().destroySwapchainKHR(m_swapChain, nullptr);
	}



	vk::SurfaceFormat2KHR SwapChain::s_chooseFormats(const std::vector<vk::SurfaceFormat2KHR> &formats)
	{
		for (const auto &format : formats)
		{
			if (format.surfaceFormat.format == vk::Format::eR8G8B8A8Srgb
				&& format.surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
				return format;
		}

		return formats[0];
	}



	vk::PresentModeKHR SwapChain::s_choosePresentMode(
		const std::vector<vk::PresentModeKHR> &presentModes, pl::graphics::Efficency efficiency
	)
	{
		if (efficiency == pl::graphics::Efficency::efficient)
			return vk::PresentModeKHR::eFifo;

		for (const auto &presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eMailbox)
				return presentMode;
		}

		return vk::PresentModeKHR::eFifo;
	}



	vk::Extent2D SwapChain::s_chooseExtent(const vk::SurfaceCapabilities2KHR &capabilities, SDL_Window *window)
	{
		if (capabilities.surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return capabilities.surfaceCapabilities.currentExtent;

		int width {}, height {};
		if (SDL_GetWindowSizeInPixels(window, &width, &height) != 0)
			throw std::runtime_error("PL : Vulkan can't get window size in pixels : " + std::string(SDL_GetError()));

		vk::Extent2D extent {static_cast<uint32_t> (width), static_cast<uint32_t> (height)};
		extent.width = std::clamp(
			extent.width, capabilities.surfaceCapabilities.minImageExtent.width, capabilities.surfaceCapabilities.maxImageExtent.width
		);
		extent.height = std::clamp(
			extent.height, capabilities.surfaceCapabilities.minImageExtent.height, capabilities.surfaceCapabilities.maxImageExtent.height
		);

		return extent;
	}



} // namespace pl::impl::vulkan
