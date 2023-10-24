#pragma once

#include "../../instance.hpp"


namespace pl::opengl
{
	class Instance
	{
		public:
			static void setup(pl::InstanceImplementation *impl, const pl::InstanceCreateInfo &createInfo);
			static void cleanup(pl::InstanceImplementation *impl);
			static void run(pl::InstanceImplementation *impl);
	};
} // namespace pl::SDL2::software
