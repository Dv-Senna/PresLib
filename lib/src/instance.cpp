#include <stdexcept>

#include "impl/SDL2/software/instance.hpp"

#include "instance.hpp"



namespace pl
{
	pl::InstanceImplementation chooseImplementation(const pl::InstanceCreateInfo &createInfo)
	{
		pl::InstanceImplementation implementation {};

		if (createInfo.windowApi == pl::WindowApi::SDL2)
		{
			if (createInfo.graphicsApi == pl::GraphicsApi::Software)
			{
				implementation.setup = pl::SDL2::software::Instance::setup;
				implementation.cleanup = pl::SDL2::software::Instance::cleanup;
				implementation.run = pl::SDL2::software::Instance::run;

				return implementation;
			}

			else if (createInfo.graphicsApi == pl::GraphicsApi::OpenGL)
				throw std::invalid_argument("PL : Can't use the OpenGL renderer yet");

			else if (createInfo.graphicsApi == pl::GraphicsApi::Vulkan)
				throw std::invalid_argument("PL : Can't use the Vulkan renderer yet");

			else if (createInfo.graphicsApi == pl::GraphicsApi::DirectX11)
				throw std::invalid_argument("PL : Can't use the DirectX11 renderer yet");

			else if (createInfo.graphicsApi == pl::GraphicsApi::DirectX12)
				throw std::invalid_argument("PL : Can't use the DirectX12 renderer yet");
		}

		else if (createInfo.windowApi == pl::WindowApi::SDL3)
			throw std::invalid_argument("PL : Can't use SDL3 as a window api yet");

		else if (createInfo.windowApi == pl::WindowApi::glfw)
			throw std::invalid_argument("PL : Can't use glfw as a window api yet");

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
