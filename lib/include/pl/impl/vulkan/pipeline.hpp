#pragma once

#include <vulkan/vulkan.hpp>

#include "../../graphics/pipeline.hpp"
#include "device.hpp"
#include "shader.hpp"
#include "swapChain.hpp"



namespace pl::impl::vulkan
{
	class Pipeline final
	{
		public:
			Pipeline(
				pl::impl::vulkan::Device &device,
				pl::impl::vulkan::SwapChain &swapChain,
				const std::vector<pl::impl::vulkan::Shader *> &shaders,
				const pl::graphics::Pipeline &createInfo
			);
			~Pipeline();

			vk::Pipeline getPipeline() const noexcept;
			vk::PipelineLayout getLayout() const noexcept;
			vk::RenderPass getRenderPass() const noexcept;


		private:
			pl::impl::vulkan::Device &m_device;
			pl::impl::vulkan::SwapChain &m_swapChain;
			vk::Pipeline m_pipeline;
			vk::PipelineLayout m_layout;
			vk::RenderPass m_renderPass;
	};

} // namespace pl::impl::vulkan
