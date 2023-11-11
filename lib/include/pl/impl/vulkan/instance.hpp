#pragma once

#include <fstream>

#include <vulkan/vulkan.hpp>

#include "../../renderer.hpp"


namespace pl::impl::vulkan
{
	class Instance final
	{
		public:
			Instance(const pl::Renderer::CreateInfo &rendererCreateInfo);
			~Instance();

			vk::Instance getInstance() const noexcept;
			const std::vector<const char *> &getExtensions() const noexcept;
			const std::vector<const char *> &getValidationLayers() const noexcept;
			std::ostream &getLogStream() noexcept;
			bool isComplet() const noexcept;

		
		private:
			void m_checkExtensionsValidity();
			void m_checkValidationLayersValidity();
			void m_setupDebugCallback();

			static VKAPI_ATTR VkBool32 VKAPI_CALL s_debugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData
			);

			vk::Instance m_instance;
			std::vector<const char *> m_extensions, m_validationLayers;
			std::ofstream m_logStream;

			#ifndef NDEBUG
				VkDebugUtilsMessengerEXT m_debugMessenger;
			#endif
	};

} // namespace pl::impl::vulkan
