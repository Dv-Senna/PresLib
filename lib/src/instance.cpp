#include <stdexcept>

#include "impl/opengl/instance.hpp"

#include "instance.hpp"



namespace pl
{
	pl::InstanceImplementation chooseImplementation(const pl::InstanceCreateInfo &createInfo)
	{
		pl::InstanceImplementation implementation {};

		if (createInfo.graphicsApi == pl::GraphicsApi::OpenGL)
		{
			implementation.setup = pl::opengl::Instance::setup;
			implementation.cleanup = pl::opengl::Instance::cleanup;
			implementation.run = pl::opengl::Instance::run;

			return implementation;
		}

		else if (createInfo.graphicsApi == pl::GraphicsApi::Vulkan)
			throw std::invalid_argument("PL : Can't use the Vulkan renderer yet");

		else if (createInfo.graphicsApi == pl::GraphicsApi::DirectX11)
			throw std::invalid_argument("PL : Can't use the DirectX11 renderer yet");

		else if (createInfo.graphicsApi == pl::GraphicsApi::DirectX12)
			throw std::invalid_argument("PL : Can't use the DirectX12 renderer yet");


		return implementation;
	}


	Instance::Instance(const pl::InstanceCreateInfo &createInfo) : 
		m_impl {pl::chooseImplementation(createInfo)}
	{
		if (m_impl.setup == nullptr || m_impl.cleanup == nullptr || m_impl.run == nullptr)
			throw std::runtime_error("PL : No implementation was choosen for the instance");
		
		m_impl.setup(&m_impl, createInfo);
	}



	Instance::~Instance()
	{
		if (m_impl.cleanup != nullptr)
			m_impl.cleanup(&m_impl);
	}



	void Instance::run()
	{
		if (m_impl.run != nullptr)
			m_impl.run(&m_impl);
	}



} // namespace pl
