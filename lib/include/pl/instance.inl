#pragma once

#include "instance.hpp"
#include "impl/SDL2_renderer/instance.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	Instance<API>::Instance() : m_impl {nullptr}
	{
		if constexpr (API == pl::GraphicsApi::SDL2_renderer)
			m_impl = new pl::impl::SDL2_renderer::Instance();
		else if constexpr (API == pl::GraphicsApi::OpenGL)
			static_assert(!(API == pl::GraphicsApi::OpenGL), "PL : OpenGL isn't supported for the moment (but is planned to be)");
		else if constexpr (API == pl::GraphicsApi::Vulkan)
			static_assert(!(API == pl::GraphicsApi::Vulkan), "PL : Vulkan isn't supported for the moment (but is planned to be)");
	}



	template <pl::GraphicsApi API>
	Instance<API>::~Instance()
	{
		if (m_impl != nullptr)
			delete m_impl;
	}



	template <pl::GraphicsApi API>
	void Instance<API>::run()
	{
		m_impl->run();
	}



	template <pl::GraphicsApi API>
	std::any Instance<API>::getHandler() const noexcept
	{
		return m_impl->getHandler();
	}



	template <pl::GraphicsApi API>
	void Instance<API>::setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept
	{
		m_impl->setRenderingCallback(callback);
	}



	template <pl::GraphicsApi API>
	std::any Instance<API>::getWindow() const noexcept
	{
		return m_impl->getWindow();
	}



	template <pl::GraphicsApi API>
	const pl::utils::WindowInfos &Instance<API>::getWindowInfos() const noexcept
	{
		return m_impl->getWindowInfos();
	}



	template <pl::GraphicsApi API>
	pl::impl::Instance *Instance<API>::getImplementation() const noexcept
	{
		return m_impl;
	}



	template <pl::GraphicsApi API>
	pl::FontManager &Instance<API>::getFonts() noexcept
	{
		return m_impl->getFonts();
	}



	template <pl::GraphicsApi API>
	void Instance<API>::addSlide(pl::Slide *slide)
	{
		m_impl->addSlide(slide);
	}



} // namespace pl
