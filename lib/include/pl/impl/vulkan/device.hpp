#pragma once

#include <map>

#include <vulkan/vulkan.hpp>

#include "instance.hpp"



namespace pl::impl::vulkan
{
	struct QueueFamiliesProperties
	{
		std::map<vk::QueueFlagBits, std::vector<std::vector<vk::QueueFamilyProperties2>::iterator>> properties;
		std::vector<vk::QueueFamilyProperties2> rawProperties;
	};

	struct Queues
	{
		std::map<vk::QueueFlagBits, std::vector<std::vector<vk::Queue>::iterator>> queues;
		std::vector<vk::Queue> rawQueues;
	};

	struct PhysicalDeviceProperties
	{
		vk::PhysicalDevice device {};
		int score {0};
		pl::impl::vulkan::QueueFamiliesProperties queueFamilies {};
		vk::PhysicalDeviceProperties2 properties {};
		vk::PhysicalDeviceFeatures2 features {};
	};

	class Device final
	{
		public:
			Device(pl::impl::vulkan::Instance &instance, pl::graphics::Efficency efficency);
			~Device();

			const pl::impl::vulkan::PhysicalDeviceProperties &getPhysicalDevice() const noexcept;
			vk::Device getDevice() const noexcept;
			const std::vector<const char *> &getExtensions() const noexcept;
			const std::vector<vk::QueueFlagBits> &getLoadedQueues() const noexcept;
			const vk::PhysicalDeviceFeatures &getLoadedFeatures() const noexcept;
			const pl::impl::vulkan::Queues &getQueues() const noexcept;

			bool isComplet() const noexcept;

		
		private:
			void m_selectPhysicalDevice(pl::graphics::Efficency efficency);
			pl::impl::vulkan::PhysicalDeviceProperties m_retrievePhysicalDeviceInformations(
				vk::PhysicalDevice device, pl::graphics::Efficency efficency
			);
			void m_createDevice();

			static pl::impl::vulkan::QueueFamiliesProperties s_retrievePhysicalDeviceQueueProperties(vk::PhysicalDevice device);

			pl::impl::vulkan::Instance &m_instance;
			pl::impl::vulkan::PhysicalDeviceProperties m_physicalDevice;
			vk::Device m_device;
			std::vector<const char *> m_extensions;
			std::vector<vk::QueueFlagBits> m_loadedQueues;
			vk::PhysicalDeviceFeatures m_loadedFeatures;
			pl::impl::vulkan::Queues m_queues;
	};

} // namespace pl::impl::vulkan
