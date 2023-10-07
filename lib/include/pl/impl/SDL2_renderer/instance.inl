#include "instance.hpp"



namespace pl::impl::SDL2_renderer
{
	const std::any &Instance::getWindow() const noexcept
	{
		return m_window;
	}


	
} // namespace pl::impl::SDL2_renderer
