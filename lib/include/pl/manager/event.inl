#include "../impl/SDL2_renderer/manager/event.hpp"
#include "event.hpp"



namespace pl::manager
{
	template <pl::GraphicsApi API>
	Event<API>::Event() : 
		m_impl {nullptr}
	{
		if constexpr (API == pl::GraphicsApi::SDL2_renderer)
			m_impl = new pl::impl::SDL2_renderer::manager::Event();
		else if constexpr (API == pl::GraphicsApi::SDL3_gpu)
			static_assert(false, "PL : graphics api 'SDL3_gpu' not yet implemented");
		else if constexpr (API == pl::GraphicsApi::OpenGL)
			static_assert(false, "PL : graphics api 'OpenGL' not yet implemented");
		else if constexpr (API == pl::GraphicsApi::Vulkan)
			static_assert(false, "PL : graphics api 'Vulkan' not yet implemented");

		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't allocate memory for event manager's implementation");
	}



	template <pl::GraphicsApi API>
	Event<API>::~Event()
	{
		if (m_impl != nullptr)
			delete m_impl;
	}



	template <pl::GraphicsApi API>
	inline bool Event<API>::process()
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't process event because the implementation has not been initialized");

		return m_impl->process();
	}



	template <pl::GraphicsApi API>
	pl::impl::manager::Event *Event<API>::getImplementation() const
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't get event's implementation because the implementation has not been initialized");

		return m_impl;
	}



	template <pl::GraphicsApi API>
	inline const std::array<pl::utils::KeyState, PL_KEYS_COUNT> &Event<API>::getKeys() const
	{
		if (m_impl == nullptr)
			throw std::runtime_error("PL : Can't get keys because the implementation has not been initialized");

		return m_impl->getKeys();
	}



} // namespace pl::manager
