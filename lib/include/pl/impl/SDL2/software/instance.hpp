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

			static void setup(pl::Instance::Implementation *impl, const pl::Instance::CreateInfo &createInfo);
			static void cleanup(pl::Instance::Implementation *impl);
			static void run(pl::Instance::Implementation *impl);
	};
} // namespace pl::SDL2::software
