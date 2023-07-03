#pragma once

#include "instance.hpp"


namespace pl::impl::SDL2_gpu
{
	std::any Instance::getHandler() const noexcept
	{
		return m_window;
	}



} // namespace pl::impl::SDL2_gpu
