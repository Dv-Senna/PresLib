#pragma once

#include <map>

#include <glm/glm.hpp>
#include <SDL3/SDL.h>


namespace pl
{
	class EventManager final
	{
		public:
			EventManager();
			~EventManager() = default;

			bool pollEvent();

			bool isKeyDown(SDL_Scancode key) const;
			bool isKeyPressed(SDL_Scancode key) const;
			bool isKeyReleased(SDL_Scancode key) const;
			const glm::vec2 &getMouseMotion() const noexcept;
			const glm::vec2 &getMousePosition() const noexcept;
			bool isButtonDown(uint8_t button) const;


		private:
			std::map<SDL_Scancode, bool> m_downKeys, m_pressedKeys, m_releasedKeys;
			glm::vec2 m_mouseMotion, m_mousePosition;
			std::map<uint8_t, bool> m_downButtons;
	};

} // namespace pl
