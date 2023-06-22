#pragma once

#include <cinttypes>
#include <string>


namespace pl::utils
{
	struct WindowInfos
	{
		int width;
		int height;
		std::string title;
		uint32_t flags;
	};

} // namespace pl::utils
