#pragma once

#include <map>

#include <vulkan/vulkan.hpp>

#include "instance.hpp"
#include "surface.hpp"



namespace pl::impl::vulkan
{
	enum class QueueFlagBits
	{
		eCompute        = 0b00000001,
		eGraphics       = 0b00000010,
		ePresentKHR     = 0b00000100,
		eProtected      = 0b00001000,
		eSparseBinding  = 0b00010000,
		eTransfer       = 0b00100000,
		eVideoDecodeKHR = 0b01000000
	};


	struct QueueFamiliesProperties
	{
		std::map<pl::impl::vulkan::QueueFlagBits, std::vector<std::vector<vk::QueueFamilyProperties2>::iterator>> properties;
		std::vector<vk::QueueFamilyProperties2> rawProperties;
	};

	struct Queues
	{
		std::map<pl::impl::vulkan::QueueFlagBits, std::vector<std::vector<vk::Queue>::iterator>> queues;
		std::vector<vk::Queue> rawQueues;
	};

	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilities2KHR capabilities;
		std::vector<vk::SurfaceFormat2KHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	struct PhysicalDeviceProperties
	{
		vk::PhysicalDevice device {};
		int score {0};
		pl::impl::vulkan::QueueFamiliesProperties queueFamilies {};
		vk::PhysicalDeviceProperties2 properties {};
		vk::PhysicalDeviceFeatures2 features {};
		pl::impl::vulkan::SwapChainSupportDetails swapChainSupportDetails;
	};


	bool isQueueSupportingFlag(
		vk::PhysicalDevice device,
		vk::SurfaceKHR surface,
		pl::impl::vulkan::QueueFlagBits flag,
		vk::QueueFlags queueFlags,
		uint32_t index
	);


	class Device final
	{
		public:
			Device(pl::impl::vulkan::Instance &instance, pl::impl::vulkan::Surface &surface, pl::graphics::Efficency efficency);
			~Device();

			const pl::impl::vulkan::PhysicalDeviceProperties &getPhysicalDevice() const noexcept;
			vk::Device getDevice() const noexcept;
			const std::vector<const char *> &getExtensions() const noexcept;
			const std::vector<pl::impl::vulkan::QueueFlagBits> &getLoadedQueues() const noexcept;
			const vk::PhysicalDeviceFeatures &getLoadedFeatures() const noexcept;
			const pl::impl::vulkan::Queues &getQueues() const noexcept;

			bool isComplet() const noexcept;

		
		private:
			void m_selectPhysicalDevice(pl::graphics::Efficency efficency);
			pl::impl::vulkan::PhysicalDeviceProperties m_retrievePhysicalDeviceInformations(
				vk::PhysicalDevice device, pl::graphics::Efficency efficency
			);
			void m_createDevice();

			static pl::impl::vulkan::QueueFamiliesProperties s_retrievePhysicalDeviceQueueProperties(
				vk::PhysicalDevice device,
				vk::SurfaceKHR surface
			);
			static pl::impl::vulkan::SwapChainSupportDetails s_retrieveSwapChainSupportDetails(
				vk::PhysicalDevice device,
				vk::SurfaceKHR surface
			);

			pl::impl::vulkan::Instance &m_instance;
			pl::impl::vulkan::Surface &m_surface;
			pl::impl::vulkan::PhysicalDeviceProperties m_physicalDevice;
			vk::Device m_device;
			std::vector<const char *> m_extensions;
			std::vector<pl::impl::vulkan::QueueFlagBits> m_loadedQueues;
			vk::PhysicalDeviceFeatures m_loadedFeatures;
			pl::impl::vulkan::Queues m_queues;
	};

} // namespace pl::impl::vulkan
