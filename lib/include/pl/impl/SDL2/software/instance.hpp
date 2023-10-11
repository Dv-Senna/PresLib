#pragma once

#include <SDL2/SDL.h>

#include "../../../instance.hpp"


namespace pl::SDL2::software
{
	class Instance
	{
		public:
			struct InternalState
			{
				SDL_Window *window;
				SDL_Renderer *renderer;
			};

			static void setup(pl::InstanceImplementation *impl, const pl::InstanceCreateInfo &createInfo);
			static void cleanup(pl::InstanceImplementation *impl);
			static void run(pl::InstanceImplementation *impl);
	};
} // namespace pl::SDL2::software
