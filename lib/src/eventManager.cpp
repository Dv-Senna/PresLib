#include "eventManager.hpp"



namespace pl
{
	EventManager::EventManager() : 
		m_downKeys {},
		m_pressedKeys {},
		m_releasedKeys {},
		m_mouseMotion {0.f, 0.f},
		m_mousePosition {0.f, 0.f},
		m_downButtons {}
	{

	}



	bool EventManager::pollEvent()
	{
		static SDL_Event event {};
		auto pastDownKeys {m_downKeys};
		m_mouseMotion = {0.f, 0.f};

		for (auto &key : m_pressedKeys)
			key.second = false;
		for (auto &key : m_releasedKeys)
			key.second = false;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_KEY_DOWN:
					m_downKeys[event.key.keysym.scancode] = true;
					break;

				case SDL_EVENT_KEY_UP:
					m_downKeys[event.key.keysym.scancode] = false;
					break;

				case SDL_EVENT_MOUSE_MOTION:
					m_mouseMotion = {event.motion.xrel, event.motion.yrel};
					m_mousePosition = {event.motion.x, event.motion.y};
					break;

				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					m_downButtons[event.button.button] = true;
					break;

				case SDL_EVENT_MOUSE_BUTTON_UP:
					m_downButtons[event.button.button] = false;
					break;

				case SDL_EVENT_QUIT:
					return false;
			}
		}

		for (const auto &keyDown : m_downKeys)
		{
			auto it {pastDownKeys.find(keyDown.first)};
			if (it == pastDownKeys.end())
			{
				m_pressedKeys[keyDown.first] = true;
				continue;
			}

			if (keyDown.second && !it->second)
				m_pressedKeys[keyDown.first] = true;
			
			else if (!keyDown.second && it->second)
				m_releasedKeys[keyDown.first] = true;
		}

		return true;
	}



	bool EventManager::isKeyDown(SDL_Scancode key) const
	{
		auto it {m_downKeys.find(key)};
		if (it == m_downKeys.end())
			return false;

		return it->second;
	}



	bool EventManager::isKeyPressed(SDL_Scancode key) const
	{
		auto it {m_pressedKeys.find(key)};
		if (it == m_pressedKeys.end())
			return false;

		return it->second;
	}



	bool EventManager::isKeyReleased(SDL_Scancode key) const
	{
		auto it {m_releasedKeys.find(key)};
		if (it == m_releasedKeys.end())
			return false;

		return it->second;
	}



	const glm::vec2 &EventManager::getMouseMotion() const noexcept
	{
		return m_mouseMotion;
	}



	const glm::vec2 &EventManager::getMousePosition() const noexcept
	{
		return m_mousePosition;
	}



	bool EventManager::isButtonDown(uint8_t button) const
	{
		auto it {m_downButtons.find(button)};
		if (it == m_downButtons.end())
			return false;

		return it->second;
	}



} // namespace pl
