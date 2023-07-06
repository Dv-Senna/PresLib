#pragma once

#include "instance.hpp"


namespace pl::impl::SDL2_renderer
{
	std::any Instance::getHandler() const noexcept
	{
		return m_handler;
	}



} // namespace pl::impl::SDL2_renderer
