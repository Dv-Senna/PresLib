#include <SDL2/SDL.h>

#include "utils/keys.hpp"



namespace pl::utils
{
	size_t convertSDL2KeysToPL(pl::utils::SDL2_Scancode key)
	{
		if (key >= SDL_SCANCODE_A && key <= SDL_SCANCODE_Z)
			return key - SDL_SCANCODE_A;

		if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_0)
			return key - SDL_SCANCODE_1;

		switch (key)
		{
			case SDL_SCANCODE_ESCAPE:
				return pl::utils::keys::escape;
			case SDL_SCANCODE_SPACE:
				return pl::utils::keys::space;
			case SDL_SCANCODE_LEFT:
				return pl::utils::keys::left;
			case SDL_SCANCODE_RIGHT:
				return pl::utils::keys::right;
			case SDL_SCANCODE_UP:
				return pl::utils::keys::up;
			case SDL_SCANCODE_DOWN:
				return pl::utils::keys::down;
			default:
				return pl::utils::keys::unknown;
		}
	}



} // namespace pl::impl
