#include "impl/vulkan/pipeline.hpp"



namespace pl::impl::vulkan
{
	Pipeline::Pipeline(
		pl::impl::vulkan::Device &device,
		pl::impl::vulkan::SwapChain &swapChain,
		const std::vector<pl::impl::vulkan::Shader *> &shaders,
		const pl::graphics::Pipeline &createInfo
	) : 
		m_device {device},
		m_swapChain {swapChain},
		m_pipeline {},
		m_layout {},
		m_renderPass {}
	{
		static std::vector<vk::DynamicState> dynamicStates {
			vk::DynamicState::eViewport,
			vk::DynamicState::eScissor
			//vk::DynamicState::ePolygonModeEXT
		};

		vk::PipelineDynamicStateCreateInfo dynamicStateCreateInfo {};
		dynamicStateCreateInfo.dynamicStateCount = dynamicStates.size();
		dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

		/*int stride {0};
		for (const auto &channel : createInfo.format.channels)
		{
			stride += channel.second.dimension;
		}

		std::vector<vk::VertexInputBindingDescription> vertexInputBindingDescriptions {};
		for (const auto &channel : createInfo.format.channels)
		{
			vertexInputBindingDescriptions.push_back({});
			vertexInputBindingDescriptions.rbegin()->binding = channel.second.location;
			vertexInputBindingDescriptions.rbegin()->stride = stride;
			vertexInputBindingDescriptions.rbegin()->inputRate = vk::VertexInputRate::eVertex;
		}*/


		vk::PipelineVertexInputStateCreateInfo vertexInputStateCreateInfo {};
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = 0;
		vertexInputStateCreateInfo.pVertexBindingDescriptions = nullptr;
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = nullptr;

		vk::PipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo {};
		inputAssemblyStateCreateInfo.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssemblyStateCreateInfo.primitiveRestartEnable = vk::False;

		vk::PipelineViewportStateCreateInfo viewportStateCreateInfo {};
		viewportStateCreateInfo.scissorCount = 1;
		viewportStateCreateInfo.viewportCount = 1;

		vk::PipelineRasterizationStateCreateInfo rasterizationStateCreateInfo {};
		rasterizationStateCreateInfo.depthClampEnable = vk::False;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = vk::False;
		rasterizationStateCreateInfo.polygonMode = vk::PolygonMode::eFill; // set it through vkCmdSetPolygonModeEXT
		rasterizationStateCreateInfo.lineWidth = 1.f;
		rasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
		rasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		rasterizationStateCreateInfo.depthBiasEnable = vk::False;
		rasterizationStateCreateInfo.depthBiasConstantFactor = 0.f;
		rasterizationStateCreateInfo.depthBiasClamp = 0.f;
		rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.f;

		vk::PipelineMultisampleStateCreateInfo multisampleStateCreateInfo {};
		multisampleStateCreateInfo.sampleShadingEnable = vk::False;
		multisampleStateCreateInfo.rasterizationSamples = vk::SampleCountFlagBits::e1;
		multisampleStateCreateInfo.minSampleShading = 1.f;
		multisampleStateCreateInfo.pSampleMask = nullptr;
		multisampleStateCreateInfo.alphaToCoverageEnable = vk::False;
		multisampleStateCreateInfo.alphaToOneEnable = vk::False;

		vk::PipelineColorBlendAttachmentState colorBlendAttachmentState {};
		colorBlendAttachmentState.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
			| vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachmentState.blendEnable = vk::True;
		colorBlendAttachmentState.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
		colorBlendAttachmentState.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
		colorBlendAttachmentState.colorBlendOp = vk::BlendOp::eAdd;
		colorBlendAttachmentState.srcAlphaBlendFactor = vk::BlendFactor::eOne;
		colorBlendAttachmentState.dstAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachmentState.alphaBlendOp = vk::BlendOp::eAdd;

		vk::PipelineColorBlendStateCreateInfo colorBlendStateCreateInfo {};
		colorBlendStateCreateInfo.logicOpEnable = vk::False;
		colorBlendStateCreateInfo.logicOp = vk::LogicOp::eCopy;
		colorBlendStateCreateInfo.attachmentCount = 1;
		colorBlendStateCreateInfo.pAttachments = &colorBlendAttachmentState;
		colorBlendStateCreateInfo.blendConstants[0] = 0.f;
		colorBlendStateCreateInfo.blendConstants[1] = 0.f;
		colorBlendStateCreateInfo.blendConstants[2] = 0.f;
		colorBlendStateCreateInfo.blendConstants[3] = 0.f;

		vk::PipelineLayoutCreateInfo layoutCreateInfo {};
		layoutCreateInfo.setLayoutCount = 0;
		layoutCreateInfo.pSetLayouts = nullptr;
		layoutCreateInfo.pushConstantRangeCount = 0;
		layoutCreateInfo.pPushConstantRanges = nullptr;

		m_layout = m_device.getDevice().createPipelineLayout(layoutCreateInfo, nullptr);


		vk::AttachmentDescription colorAttachmentDescription {};
		colorAttachmentDescription.format = m_swapChain.getFormat();
		colorAttachmentDescription.samples = vk::SampleCountFlagBits::e1;
		colorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		colorAttachmentDescription.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		colorAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
		colorAttachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		vk::AttachmentReference colorAttachmentReference {};
		colorAttachmentReference.attachment = 0;
		colorAttachmentReference.layout = vk::ImageLayout::eColorAttachmentOptimal;

		vk::SubpassDescription subpassDescription {};
		subpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &colorAttachmentReference;
		subpassDescription.pDepthStencilAttachment = nullptr;

		vk::RenderPassCreateInfo renderPassCreateInfo {};
		renderPassCreateInfo.attachmentCount = 1;
		renderPassCreateInfo.pAttachments = &colorAttachmentDescription;
		renderPassCreateInfo.subpassCount = 1;
		renderPassCreateInfo.pSubpasses = &subpassDescription;

		m_renderPass = m_device.getDevice().createRenderPass(renderPassCreateInfo, nullptr);


		std::vector<vk::PipelineShaderStageCreateInfo> shaderStages {};
		shaderStages.reserve(shaders.size());
		for (const auto &shader : shaders)
			shaderStages.push_back(shader->getShaderStageCreateInfo());

		vk::GraphicsPipelineCreateInfo pipelineCreateInfo {};
		pipelineCreateInfo.stageCount = shaderStages.size();
		pipelineCreateInfo.pStages = shaderStages.data();
		pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
		pipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
		pipelineCreateInfo.pDepthStencilState = nullptr;
		pipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
		pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
		pipelineCreateInfo.layout = m_layout;
		pipelineCreateInfo.renderPass = m_renderPass,
		pipelineCreateInfo.subpass = 0;
		pipelineCreateInfo.basePipelineHandle = nullptr;
		pipelineCreateInfo.basePipelineIndex = -1;

		auto pipelineCreationResult {m_device.getDevice().createGraphicsPipeline(nullptr, pipelineCreateInfo, nullptr)};
		if (pipelineCreationResult.result != vk::Result::eSuccess)
			throw std::runtime_error("PL : Vulkan can't create pipeline");

		m_pipeline = pipelineCreationResult.value;
	}



	Pipeline::~Pipeline()
	{
		m_device.getDevice().destroyPipeline(m_pipeline, nullptr);
		m_device.getDevice().destroyRenderPass(m_renderPass, nullptr);
		m_device.getDevice().destroyPipelineLayout(m_layout, nullptr);
	}



	vk::Pipeline Pipeline::getPipeline() const noexcept
	{
		return m_pipeline;
	}



	vk::PipelineLayout Pipeline::getLayout() const noexcept
	{
		return m_layout;
	}



	vk::RenderPass Pipeline::getRenderPass() const noexcept
	{
		return m_renderPass;
	}



} // namespace pl::impl::vulkan
