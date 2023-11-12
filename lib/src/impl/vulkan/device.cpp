#include <stdexcept>

#include "config.hpp"
#include "impl/vulkan/device.hpp"



namespace pl::impl::vulkan
{
	const std::vector<pl::impl::vulkan::QueueFlagBits> ALL_QUEUE_FLAG_BITS {
		pl::impl::vulkan::QueueFlagBits::eCompute,
		pl::impl::vulkan::QueueFlagBits::eGraphics,
		pl::impl::vulkan::QueueFlagBits::ePresentKHR,
		pl::impl::vulkan::QueueFlagBits::eProtected,
		pl::impl::vulkan::QueueFlagBits::eSparseBinding,
		pl::impl::vulkan::QueueFlagBits::eTransfer,
		pl::impl::vulkan::QueueFlagBits::eVideoDecodeKHR
	};



	bool isQueueSupportingFlag(
		vk::PhysicalDevice device,
		vk::SurfaceKHR surface,
		pl::impl::vulkan::QueueFlagBits flag,
		vk::QueueFlags queueFlags,
		uint32_t index
	)
	{
		static std::map<pl::impl::vulkan::QueueFlagBits, vk::QueueFlagBits> flagConversion {
			{pl::impl::vulkan::QueueFlagBits::eCompute, vk::QueueFlagBits::eCompute},	
			{pl::impl::vulkan::QueueFlagBits::eGraphics, vk::QueueFlagBits::eGraphics},
			{pl::impl::vulkan::QueueFlagBits::eProtected, vk::QueueFlagBits::eProtected},
			{pl::impl::vulkan::QueueFlagBits::eSparseBinding, vk::QueueFlagBits::eSparseBinding},
			{pl::impl::vulkan::QueueFlagBits::eTransfer, vk::QueueFlagBits::eTransfer},
			{pl::impl::vulkan::QueueFlagBits::eVideoDecodeKHR, vk::QueueFlagBits::eVideoDecodeKHR}
		};

		if (flag == pl::impl::vulkan::QueueFlagBits::ePresentKHR)
		{
			VkBool32 isSupported {};
			vkGetPhysicalDeviceSurfaceSupportKHR(device, index, surface, &isSupported);
			return isSupported;
		}

		return (queueFlags & flagConversion[flag]) != vk::QueueFlags();
	}



	Device::Device(pl::impl::vulkan::Instance &instance, pl::impl::vulkan::Surface &surface, pl::graphics::Efficency efficency) :
		m_instance {instance},
		m_surface {surface},
		m_physicalDevice {},
		m_device {},
		m_extensions {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		},
		m_loadedQueues {
			pl::impl::vulkan::QueueFlagBits::eGraphics,
			pl::impl::vulkan::QueueFlagBits::ePresentKHR
		},
		m_loadedFeatures {},
		m_queues {}
	{
		this->m_selectPhysicalDevice(efficency);
		this->m_createDevice();

		m_instance.getLogStream() << "PL : Vulkan the following queues were created : \n";

		for (const auto &queue : m_queues.queues)
		{
			if (queue.second.empty())
				continue;
			
			switch (queue.first)
			{
				case pl::impl::vulkan::QueueFlagBits::eCompute:
					m_instance.getLogStream() << "\tcompute (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::eGraphics:
					m_instance.getLogStream() << "\tgraphics (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::ePresentKHR:
					m_instance.getLogStream() << "\tpresentKHR (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::eProtected:
					m_instance.getLogStream() << "\tprotected (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::eSparseBinding:
					m_instance.getLogStream() << "\tsparseBinding (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::eTransfer:
					m_instance.getLogStream() << "\ttransfer (" << queue.second.size() << ")\n";
					break;

				case pl::impl::vulkan::QueueFlagBits::eVideoDecodeKHR:
					m_instance.getLogStream() << "\tvideoDecodeKHR (" << queue.second.size() << ")\n";
					break;
			}
		}

		m_instance.getLogStream() << std::endl;

		m_instance.getLogStream() << "PL : Vulkan the following device extensions were loaded :\n";

		for (const auto &extension : m_extensions)
			m_instance.getLogStream() << "\t" << extension << "\n";

		m_instance.getLogStream() << std::endl;
	}



	Device::~Device()
	{
		m_device.destroy(nullptr);
	}



	const pl::impl::vulkan::PhysicalDeviceProperties &Device::getPhysicalDevice() const noexcept
	{
		return m_physicalDevice;
	}



	vk::Device Device::getDevice() const noexcept
	{
		return m_device;
	}



	const std::vector<const char *> &Device::getExtensions() const noexcept
	{
		return m_extensions;
	}



	const std::vector<pl::impl::vulkan::QueueFlagBits> &Device::getLoadedQueues() const noexcept
	{
		return m_loadedQueues;
	}


	const vk::PhysicalDeviceFeatures &Device::getLoadedFeatures() const noexcept
	{
		return m_loadedFeatures;
	}


	const pl::impl::vulkan::Queues &Device::getQueues() const noexcept
	{
		return m_queues;
	}



	bool Device::isComplet() const noexcept
	{
		return m_physicalDevice.device != vk::PhysicalDevice() && m_device != vk::Device();
	}



	void Device::m_selectPhysicalDevice(pl::graphics::Efficency efficency)
	{
		uint32_t count {};

		if (m_instance.getInstance().enumeratePhysicalDevices(&count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate physical devices count");

		std::vector<vk::PhysicalDevice> physicalDevices {};
		physicalDevices.resize(count);

		if (m_instance.getInstance().enumeratePhysicalDevices(&count, physicalDevices.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate physical devices");
		

		std::vector<pl::impl::vulkan::PhysicalDeviceProperties> suitableDevice {};
		suitableDevice.reserve(physicalDevices.size());

		for (const auto &device : physicalDevices)
		{
			auto properties {this->m_retrievePhysicalDeviceInformations(device, efficency)};
			if (properties.score >= 0)
				suitableDevice.push_back(properties);
		}

		m_instance.getLogStream() << "PL : Vulkan the following physical devices are usable by PresLib :\n";

		int maxScore {-1};
		for (const auto &device : suitableDevice)
		{
			if (device.score > maxScore)
			{
				maxScore = device.score;
				m_physicalDevice = device;
			}

			m_instance.getLogStream() << "\t" << device.properties.properties.deviceName << "\n";
		}

		if (maxScore == -1)
			throw std::runtime_error("PL : Vulkan can't find suitable device for PresLib");

		m_instance.getLogStream() << std::endl;

		m_instance.getLogStream() << "PL : Vulkan choosen physical device : " << m_physicalDevice.properties.properties.deviceName << "\n" << std::endl;
	}



	pl::impl::vulkan::PhysicalDeviceProperties Device::m_retrievePhysicalDeviceInformations(
		vk::PhysicalDevice device, pl::graphics::Efficency efficency
	)
	{
		pl::impl::vulkan::PhysicalDeviceProperties properties {};
		properties.device = device;
		properties.device.getProperties2(&properties.properties);
		properties.device.getFeatures2(&properties.features);
		properties.queueFamilies = Device::s_retrievePhysicalDeviceQueueProperties(properties.device, m_surface.getSurface());
		

		if (VK_API_VERSION_MINOR(properties.properties.properties.apiVersion) < (uint32_t)pl::config::vulkanVerion.y)
		{
			properties.score = -1;
			return properties;
		}

		for (const auto queue : m_loadedQueues)
		{
			if (properties.queueFamilies.properties[queue].empty())
			{
				properties.score = -1;
				return properties;
			}
		}


		uint32_t count {};
		if (device.enumerateDeviceExtensionProperties(nullptr, &count, nullptr) != vk::Result::eSuccess)
		{
			m_instance.getLogStream() << "PL : Vulkan unable to get extensions from a device. It will be considered invalid\n" << std::endl;
			properties.score = -1;
			return properties;
		}

		std::vector<vk::ExtensionProperties> availableExtensions {};
		availableExtensions.resize(count);

		if (device.enumerateDeviceExtensionProperties(nullptr, &count, availableExtensions.data()) != vk::Result::eSuccess)
		{
			m_instance.getLogStream() << "PL : Vulkan unable to get extensions from device '" << properties.properties.properties.deviceName << "'. It will be considered invalid\n" << std::endl;
			properties.score = -1;
			return properties;
		}

		for (const auto &extension : m_extensions)
		{
			bool founded {false};

			for (const auto &available : availableExtensions)
			{
				if (strcmp(extension, available.extensionName) == 0)
				{
					founded = true;
					break;
				}
			}

			if (!founded)
			{
				m_instance.getLogStream() << "PL : Vulkan device '" << properties.properties.properties.deviceName << "' doesn't have needed extension '" << extension << "'\n" << std::endl;
				properties.score = -1;
				return properties;
			}
		}


		properties.swapChainSupportDetails = pl::impl::vulkan::Device::s_retrieveSwapChainSupportDetails(device, m_surface.getSurface());
		if (properties.swapChainSupportDetails.formats.empty() || properties.swapChainSupportDetails.presentModes.empty())
		{
			m_instance.getLogStream() << "PL : Vulkan device '" << properties.properties.properties.deviceName << "' doesn't have needed swapChain support\n" << std::endl;
				properties.score = -1;
				return properties;
		}


		switch (efficency)
		{
			case pl::graphics::Efficency::efficient:
				if (properties.properties.properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
					properties.score += 1000;
				break;
			
			case pl::graphics::Efficency::performance:
				if (properties.properties.properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
					properties.score += 1000;
				break;

			default:
				break;
		}

		return properties;
	}



	void Device::m_createDevice()
	{
		std::vector<vk::DeviceQueueCreateInfo> deviceQueueCreateInfos {};
		std::vector<vk::QueueFlags> deviceQueueFlags {};
		std::vector<bool> supportPresents {};
		float priority {1.f};

		for (size_t i {0}; i < m_physicalDevice.queueFamilies.rawProperties.size(); ++i)
		{
			const auto &queue {m_physicalDevice.queueFamilies.rawProperties[i]};

			for (const auto &loadedQueue : m_loadedQueues)
			{
				if (pl::impl::vulkan::isQueueSupportingFlag(
					m_physicalDevice.device, m_surface.getSurface(), loadedQueue, queue.queueFamilyProperties.queueFlags, i
				))
				{
					vk::DeviceQueueCreateInfo createInfo {};
					createInfo.pQueuePriorities = &priority;
					createInfo.queueCount = queue.queueFamilyProperties.queueCount;
					createInfo.queueFamilyIndex = i;
					deviceQueueCreateInfos.push_back(createInfo);
					deviceQueueFlags.push_back(queue.queueFamilyProperties.queueFlags);
					supportPresents.push_back(pl::impl::vulkan::isQueueSupportingFlag(
						m_physicalDevice.device, m_surface.getSurface(), pl::impl::vulkan::QueueFlagBits::ePresentKHR,
						queue.queueFamilyProperties.queueFlags, i
					));
				}
			}
		}


		vk::DeviceCreateInfo deviceCreateInfo {};
		deviceCreateInfo.queueCreateInfoCount = deviceQueueCreateInfos.size();
		deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
		deviceCreateInfo.enabledExtensionCount = m_extensions.size();
		deviceCreateInfo.ppEnabledExtensionNames = m_extensions.data();
		deviceCreateInfo.pEnabledFeatures = &m_loadedFeatures;

		m_device = m_physicalDevice.device.createDevice(deviceCreateInfo, nullptr);


		for (size_t i {0}; i < std::min(deviceQueueCreateInfos.size(), deviceQueueFlags.size()); ++i)
		{
			vk::Queue queue {m_device.getQueue(deviceQueueCreateInfos[i].queueFamilyIndex, 0)};
			m_queues.rawQueues.push_back(queue);

			for (const auto &flag : ALL_QUEUE_FLAG_BITS)
			{
				if (pl::impl::vulkan::isQueueSupportingFlag(
					m_physicalDevice.device, m_surface.getSurface(), flag, deviceQueueFlags[i], deviceQueueCreateInfos[i].queueFamilyIndex
				))
					m_queues.queues[flag].push_back(m_queues.rawQueues.end() - 1);
			}
		}


		m_instance.getLogStream() << "PL : Vulkan " << m_queues.queues.size() << " queues were created\n" << std::endl;
	}



	pl::impl::vulkan::QueueFamiliesProperties Device::s_retrievePhysicalDeviceQueueProperties(
		vk::PhysicalDevice device,
		vk::SurfaceKHR surface
	)
	{
		uint32_t count {};
		pl::impl::vulkan::QueueFamiliesProperties queues {};

		device.getQueueFamilyProperties2(&count, nullptr);
		std::vector<vk::QueueFamilyProperties2> queueProperties {};
		queueProperties.resize(count);
		device.getQueueFamilyProperties2(&count, queueProperties.data());
		queues.rawProperties.reserve(queueProperties.size());

		for (const auto &property : queueProperties)
		{
			queues.rawProperties.push_back(property);
		}

		for (const auto &flag : ALL_QUEUE_FLAG_BITS)
		{
			auto &it = (queues.properties[flag] = {});

			for (auto property {queues.rawProperties.begin()}; property != queues.rawProperties.end(); ++property)
			{
				if (pl::impl::vulkan::isQueueSupportingFlag(
					device, surface, flag, property->queueFamilyProperties.queueFlags, property - queues.rawProperties.begin()
				))
				//if (property->queueFamilyProperties.queueFlags & flag)
					it.push_back(property);
			}
		}

		return queues;
	}



	pl::impl::vulkan::SwapChainSupportDetails Device::s_retrieveSwapChainSupportDetails(
		vk::PhysicalDevice device,
		vk::SurfaceKHR surface
	)
	{
		uint32_t count {};
		pl::impl::vulkan::SwapChainSupportDetails supportDetails {};

		supportDetails.capabilities = device.getSurfaceCapabilities2KHR(surface);

		vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfos {};
		surfaceInfos.surface = surface;

		if (device.getSurfaceFormats2KHR(&surfaceInfos, &count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't get surface formats count");

		supportDetails.formats.resize(count);
		if (device.getSurfaceFormats2KHR(&surfaceInfos, &count, supportDetails.formats.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't get surface formats");

		if (device.getSurfacePresentModesKHR(surface, &count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't get surface present modes count");

		supportDetails.presentModes.resize(count);
		if (device.getSurfacePresentModesKHR(surface, &count, supportDetails.presentModes.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't get surface present modes");

		return supportDetails;
	}



} // namespace pl::impl::vulkan
