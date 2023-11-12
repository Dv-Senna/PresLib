#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "config.hpp"
#include "defines.hpp"
#include "impl/vulkan/instance.hpp"


VkResult vkCreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
	const VkAllocationCallbacks *pAllocator,
	VkDebugUtilsMessengerEXT *pDebugMessenger
)
{
	static auto func {(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT")};
	if (func == nullptr)
		return VK_ERROR_FEATURE_NOT_PRESENT;

	return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
}



void vkDestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks *pAllocator
)
{
	static auto func {(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT")};
	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}



namespace pl::impl::vulkan
{
	Instance::Instance(const pl::Renderer::CreateInfo &rendererCreateInfo) : 
		m_instance {},
		m_extensions {},
		m_validationLayers {"VK_LAYER_KHRONOS_validation"},
		m_logStream {"debug.vulkan.log"}

		#ifndef NDEBUG
			, m_debugMessenger {}
		#endif
	{
		vk::ApplicationInfo appInfo {};
		appInfo.pApplicationName = rendererCreateInfo.windowTitle.c_str();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "PresLib Vulkan Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(pl::defines::version.major, pl::defines::version.minor, pl::defines::version.patch);
		appInfo.apiVersion = VK_MAKE_API_VERSION(0, (int)pl::config::vulkanVerion.x, (int)pl::config::vulkanVerion.y, 0);


		this->m_checkExtensionsValidity();
		this->m_checkValidationLayersValidity();		


		vk::InstanceCreateInfo createInfo {};
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = m_extensions.size();
		createInfo.ppEnabledExtensionNames = m_extensions.data();
		createInfo.enabledLayerCount = 0;

		m_instance = vk::createInstance(createInfo, nullptr);

		this->m_setupDebugCallback();


		if (m_extensions.size() != 0)
			m_logStream << "Vulkan loaded extensions : \n";

		for (const auto &extension : m_extensions)
			m_logStream << "\t" << extension << "\n";


		#ifndef NDEBUG
			if (m_validationLayers.size() != 0)
				m_logStream << "\nVulkan loaded validation layers\n";

			for (const auto &layer : m_validationLayers)
				m_logStream << "\t" << layer << "\n";
		#endif

		m_logStream << std::endl;
	}



	Instance::~Instance()
	{
		#ifndef NDEBUG

			vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

		#endif

		m_instance.destroy();
	}



	vk::Instance Instance::getInstance() const noexcept
	{
		return m_instance;
	}



	const std::vector<const char *> &Instance::getExtensions() const noexcept
	{
		return m_extensions;
	}



	const std::vector<const char *> &Instance::getValidationLayers() const noexcept
	{
		return m_validationLayers;
	}



	std::ostream &Instance::getLogStream() noexcept
	{
		return m_logStream;
	}



	bool Instance::isComplet() const noexcept
	{
		return m_instance != vk::Instance();
	}



	void Instance::m_checkExtensionsValidity()
	{
		uint32_t count {};

		if (!SDL_Vulkan_GetInstanceExtensions(&count, nullptr))
			throw std::runtime_error("PL : Vulkan can't retrieve SDL's required vulkan extensions count");

		size_t applicationExtensions {m_extensions.size()};
		m_extensions.resize(applicationExtensions + count);
		if (!SDL_Vulkan_GetInstanceExtensions(&count, (const char**)((size_t)(m_extensions.data()) + applicationExtensions)))
			throw std::runtime_error("PL : Vulkan can't retrieve SDL's required vulkan extensions");


		std::vector<const char *> optionalExtensions {
			#ifndef NDEBUG
				"VK_EXT_debug_utils",
			#endif
		};
		std::vector<const char *> availableOptionalExtensions {};
		availableOptionalExtensions.reserve(optionalExtensions.size());


		if (vk::enumerateInstanceExtensionProperties(nullptr, &count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate instance extensions count");

		std::vector<vk::ExtensionProperties> availableExtensions {};
		availableExtensions.resize(count);

		if (vk::enumerateInstanceExtensionProperties(nullptr, &count, availableExtensions.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate instance extensions count");

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
				throw std::runtime_error("PL : Vulkan extension '" + std::string(extension) + "' is missing");
		}

		for (const auto &extension : optionalExtensions)
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
				m_logStream << "PL : Vulkan optional extension '" << extension << "' was not found. The associated functionalities won't be enabled" << std::endl;
				continue;
			}

			availableOptionalExtensions.push_back(extension);
		}

		m_extensions.insert(m_extensions.end(), availableOptionalExtensions.begin(), availableOptionalExtensions.end());
	}



	void Instance::m_checkValidationLayersValidity()
	{
		#ifndef NDEBUG

		uint32_t count {};

		if (vk::enumerateInstanceLayerProperties(&count, nullptr) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate innstance validation layers count");

		std::vector<vk::LayerProperties> availableLayers {};
		availableLayers.resize(count);

		if (vk::enumerateInstanceLayerProperties(&count, availableLayers.data()) != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't enumerate innstance validation layers count");

		std::vector<const char *> foundedLayer {};
		foundedLayer.reserve(m_validationLayers.size());

		for (const auto &layer : m_validationLayers)
		{
			bool founded {false};

			for (const auto &available : availableLayers)
			{
				if (strcmp(layer, available.layerName) == 0)
				{
					founded = true;
					break;
				}
			}

			if (!founded)
			{
				m_logStream << "PL : Vulkan validation layer '" << layer << "' was not found. The associated check won't be enabled" << std::endl;
				continue;
			}

			foundedLayer.push_back(layer);
		}

		m_validationLayers = foundedLayer;

		#else

		m_validationLayers.clear();

		#endif
	}



	void Instance::m_setupDebugCallback()
	{
		#ifndef NDEBUG

		VkDebugUtilsMessengerCreateInfoEXT createInfo {};
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
			| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		createInfo.pfnUserCallback = pl::impl::vulkan::Instance::s_debugCallback;
		createInfo.pUserData = &m_logStream;

		if (vkCreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
			m_logStream << "PL : Vulkan can't debug messenger can't be created" << std::endl;

		#endif
	}



	VKAPI_ATTR VkBool32 VKAPI_CALL Instance::s_debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* pUserData
	)
	{
		if (messageSeverity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)//VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			return vk::False;

		std::ostream &stream {*static_cast<std::ostream*> (pUserData)};
		stream << "---------------\n";

		stream << "Debug message: " << callbackData->pMessage << "\n";

		stream << "Type: ";
		if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
			stream << "general ";
		if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT)
			stream << "device_address_binding ";
		if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
			stream << "performance ";
		if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
			stream << "validation ";
		stream << "\n";


		stream << "Severity: ";
		switch (messageSeverity)
		{
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				stream << "verbose\n";
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				stream << "info\n";
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				stream << "warning\n";
				break;

			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				stream << "error\n";
				break;

			default:
				stream << "unknown\n";
				break;
		}

		stream << std::endl;

		return vk::False;
	}



} // namespace pl::impl::vulkan
