#include "impl/vulkan/shader.hpp"
#include "utils/file.hpp"



namespace pl::impl::vulkan
{
	Shader::Shader(pl::impl::vulkan::Device &device, const pl::graphics::Shader &createInfo) : 
		m_device {device},
		m_module {},
		m_stageCreateInfo {}
	{
		static std::map<pl::graphics::ShaderType, vk::ShaderStageFlagBits> shaderTypes {
			{pl::graphics::ShaderType::fragment, vk::ShaderStageFlagBits::eFragment},
			{pl::graphics::ShaderType::vertex, vk::ShaderStageFlagBits::eVertex},
			{pl::graphics::ShaderType::geometry, vk::ShaderStageFlagBits::eGeometry}
		};

		std::vector<unsigned char> fileContent {pl::utils::getBinaryFileContent(createInfo.file)};

		vk::ShaderModuleCreateInfo shaderModuleCreateInfo {};
		shaderModuleCreateInfo.codeSize = fileContent.size();
		shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t *> (fileContent.data());

		m_module = m_device.getDevice().createShaderModule(shaderModuleCreateInfo, nullptr);

		m_stageCreateInfo.stage = shaderTypes[createInfo.type];
		m_stageCreateInfo.module = m_module;
		m_stageCreateInfo.pName = createInfo.entryPoint.c_str();
		m_stageCreateInfo.pSpecializationInfo = nullptr;
	}



	Shader::~Shader()
	{
		m_device.getDevice().destroyShaderModule(m_module, nullptr);
	}



	vk::ShaderModule Shader::getModule() const noexcept
	{
		return m_module;
	}



	const vk::PipelineShaderStageCreateInfo &Shader::getShaderStageCreateInfo() const noexcept
	{
		return m_stageCreateInfo;
	}



} // namespace pl::impl::vulkan
