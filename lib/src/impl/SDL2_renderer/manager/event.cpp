#include <SDL2/SDL.h>

#include "impl/SDL2_renderer/manager/event.hpp"
#include "utils/keys.hpp"



namespace pl::impl::SDL2_renderer::manager
{
	bool Event::m_handleEvent()
	{
		static SDL_Event event {};
		std::array<pl::utils::KeyState, PL_KEYS_COUNT> beforeKeys {m_keys};

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					m_keys[pl::utils::convertSDL2KeysToPL(event.key.keysym.scancode)].isDown = true;
					break;

				case SDL_KEYUP:
					m_keys[pl::utils::convertSDL2KeysToPL(event.key.keysym.scancode)].isDown = false;
					break;

				case SDL_QUIT:
					return false;

				default:
					break;
			}
		}


		for (size_t i {0}; i < PL_KEYS_COUNT; ++i)
		{
			if (m_keys[i].isDown != beforeKeys[i].hasChanged && !m_keys[i].hasChanged)
				m_keys[i].hasChanged = true;

			else if (m_keys[i].isDown == beforeKeys[i].hasChanged && m_keys[i].hasChanged)
				m_keys[i].hasChanged = false;
		}

		return true;
	}



} // namespace pl::impl::SDL2_renderer::manager
