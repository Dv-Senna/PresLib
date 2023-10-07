#include <stdexcept>

#include "impl/SDL2_renderer/instance.hpp"
#include "instance.hpp"



namespace pl
{
	template <pl::GraphicsApi API>
	Instance<API>::Instance(const std::string &title) :
		m_impl {nullptr},
		m_manager {}
	{
		if constexpr (API == pl::GraphicsApi::SDL2_renderer)
			m_impl = new pl::impl::SDL2_renderer::Instance(title, m_manager.getImplementation());
		else if constexpr (API == pl::GraphicsApi::SDL3_gpu)
			static_assert(false, "PL : graphics api 'SDL3_gpu' not yet implemented");
		else if constexpr (API == pl::GraphicsApi::OpenGL)
			static_assert(false, "PL : graphics api 'OpenGL' not yet implemented");
		else if constexpr (API == pl::GraphicsApi::Vulkan)
			static_assert(false, "PL : graphics api 'Vulkan' not yet implemented");

		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't allocate memory for instance's implementation");
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
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't run instance because the implementation has not been initialized");

		m_impl->run();
	}



	template <pl::GraphicsApi API>
	pl::impl::Instance *Instance<API>::getImplementation() const
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't get instance's implementation because the implementation has not been initialized");

		return m_impl;
	}



	template <pl::GraphicsApi API>
	const std::any &Instance<API>::getHandler() const
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't get instance's handler because the implementation has not been initialized");

		return m_impl->getHandler();
	}



	template <pl::GraphicsApi API>
	const std::string &Instance<API>::getTitle() const
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't get instance's window's title because the implementation has not been initialized");

		return m_impl->getTitle();
	}



	template <pl::GraphicsApi API>
	const pl::Manager<API> &Instance<API>::getManager() const noexcept
	{
		return m_manager;
	}



} // namespace pl
