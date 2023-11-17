#pragma once

#include <vulkan/vulkan.hpp>

#include "../../graphics/shader.hpp"
#include "device.hpp"



namespace pl::impl::vulkan
{
	class Shader final
	{
		public:
			Shader(pl::impl::vulkan::Device &device, const pl::graphics::Shader &createInfo);
			~Shader();

			vk::ShaderModule getModule() const noexcept;
			const vk::PipelineShaderStageCreateInfo &getShaderStageCreateInfo() const noexcept;

		
		private:
			pl::impl::vulkan::Device &m_device;
			vk::ShaderModule m_module;
			vk::PipelineShaderStageCreateInfo m_stageCreateInfo;
	};

} // namespace pl::impl::vulkan
