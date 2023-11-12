#include <stdexcept>

#include "config.hpp"
#include "impl/vulkan/device.hpp"



namespace pl::impl::vulkan
{
	Device::Device(pl::impl::vulkan::Instance &instance, pl::graphics::Efficency efficency) :
		m_instance {instance},
		m_physicalDevice {},
		m_device {},
		m_extensions {},
		m_loadedQueues {
			vk::QueueFlagBits::eGraphics
		},
		m_loadedFeatures {},
		m_queues {}
	{
		this->m_selectPhysicalDevice(efficency);
		this->m_createDevice();
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



	const std::vector<vk::QueueFlagBits> &Device::getLoadedQueues() const noexcept
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
		properties.queueFamilies = Device::s_retrievePhysicalDeviceQueueProperties(properties.device);
		

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
		float priority {1.f};

		for (size_t i {0}; i < m_physicalDevice.queueFamilies.rawProperties.size(); ++i)
		{
			const auto &queue {m_physicalDevice.queueFamilies.rawProperties[i]};

			for (const auto &loadedQueue : m_loadedQueues)
			{
				if (queue.queueFamilyProperties.queueFlags & loadedQueue)
				{
					vk::DeviceQueueCreateInfo createInfo {};
					createInfo.pQueuePriorities = &priority;
					createInfo.queueCount = queue.queueFamilyProperties.queueCount;
					createInfo.queueFamilyIndex = i;
					deviceQueueCreateInfos.push_back(createInfo);
					deviceQueueFlags.push_back(queue.queueFamilyProperties.queueFlags);
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


			const std::vector<vk::QueueFlagBits> flags {
			vk::QueueFlagBits::eCompute,
			vk::QueueFlagBits::eGraphics,
			vk::QueueFlagBits::eProtected,
			vk::QueueFlagBits::eSparseBinding,
			vk::QueueFlagBits::eTransfer,
			vk::QueueFlagBits::eVideoDecodeKHR
			};

			for (const auto &flag : flags)
			{
				if (deviceQueueFlags[i] & flag)
					m_queues.queues[flag].push_back(m_queues.rawQueues.end() - 1);
			}
		}


		m_instance.getLogStream() << "PL : Vulkan " << m_queues.queues.size() << " queues were created\n" << std::endl;
	}



	pl::impl::vulkan::QueueFamiliesProperties Device::s_retrievePhysicalDeviceQueueProperties(vk::PhysicalDevice device)
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

		const std::vector<vk::QueueFlagBits> flags {
			vk::QueueFlagBits::eCompute,
			vk::QueueFlagBits::eGraphics,
			vk::QueueFlagBits::eProtected,
			vk::QueueFlagBits::eSparseBinding,
			vk::QueueFlagBits::eTransfer,
			vk::QueueFlagBits::eVideoDecodeKHR
		};

		for (const auto &flag : flags)
		{
			auto &it = (queues.properties[flag] = {});

			for (auto property {queues.rawProperties.begin()}; property != queues.rawProperties.end(); ++property)
			{
				if (property->queueFamilyProperties.queueFlags & flag)
					it.push_back(property);
			}
		}

		return queues;
	}



} // namespace pl::impl::vulkan
