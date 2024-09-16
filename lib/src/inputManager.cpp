#include "pl/inputManager.hpp"



namespace pl {
	void InputManager::update() {
		SDL_Event event {};
		s_wasWindowResized = false;

		s_oldKeyStates = s_keyStates;
		s_oldMouseButtonStates = s_mouseButtonStates;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					s_keyStates[static_cast<pl::Key> (event.key.keysym.scancode)] = true;
					break;

				case SDL_KEYUP:
					s_keyStates[static_cast<pl::Key> (event.key.keysym.scancode)] = false;
					break;

				case SDL_MOUSEMOTION:
					s_mousePosition = pl::Vec2i(event.motion.x, event.motion.y);
					s_mouseMotion = pl::Vec2i(event.motion.xrel, event.motion.yrel);
					break;

				case SDL_MOUSEBUTTONDOWN:
					s_mouseButtonStates[static_cast<pl::MouseButton> (event.button.button)] = true;
					break;

				case SDL_MOUSEBUTTONUP:
					s_mouseButtonStates[static_cast<pl::MouseButton> (event.button.button)] = false;
					break;

				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
						s_wasWindowResized = true;
					break;

				case SDL_QUIT:
					s_running = false;
					return;
			}
		}
	}


	bool InputManager::isKeyDown(pl::Key key) {
		auto it {s_keyStates.find(key)};
		if (it != s_keyStates.end())
			return it->second;
		s_keyStates[key] = false;
		return false;
	}


	bool InputManager::isKeyUp(pl::Key key) {
		auto it {s_keyStates.find(key)};
		if (it != s_keyStates.end())
			return !it->second;
		s_keyStates[key] = false;
		return true;
	}


	bool InputManager::wasKeyPressed(pl::Key key) {
		auto current {s_keyStates.find(key)};
		if (current == s_keyStates.end()) {
			s_keyStates[key] = false;
			s_oldKeyStates[key] = false;
			return false;
		}

		auto old {s_oldKeyStates.find(key)};
		if (old == s_oldKeyStates.end()) {
			s_oldKeyStates[key] = current->second;
			return false;
		}

		return current->second && !old->second;
	}


	bool InputManager::wasKeyReleased(pl::Key key) {
		auto current {s_keyStates.find(key)};
		if (current == s_keyStates.end()) {
			s_keyStates[key] = false;
			s_oldKeyStates[key] = false;
			return false;
		}

		auto old {s_oldKeyStates.find(key)};
		if (old == s_oldKeyStates.end()) {
			s_oldKeyStates[key] = current->second;
			return false;
		}

		return !current->second && old->second;
	}


	bool InputManager::isMouseButtonDown(pl::MouseButton mouseButton) {
		auto it {s_mouseButtonStates.find(mouseButton)};
		if (it != s_mouseButtonStates.end())
			return it->second;
		s_mouseButtonStates[mouseButton] = false;
		return false;
	}


	bool InputManager::isMouseButtonUp(pl::MouseButton mouseButton) {
		auto it {s_mouseButtonStates.find(mouseButton)};
		if (it != s_mouseButtonStates.end())
			return !it->second;
		s_mouseButtonStates[mouseButton] = false;
		return true;
	}


	bool InputManager::wasMouseButtonPressed(pl::MouseButton mouseButton) {
		auto current {s_mouseButtonStates.find(mouseButton)};
		if (current == s_mouseButtonStates.end()) {
			s_mouseButtonStates[mouseButton] = false;
			s_oldMouseButtonStates[mouseButton] = false;
			return false;
		}

		auto old {s_oldMouseButtonStates.find(mouseButton)};
		if (old == s_oldMouseButtonStates.end()) {
			s_oldMouseButtonStates[mouseButton] = current->second;
			return false;
		}

		return current->second && !old->second;
	}


	bool InputManager::wasMouseButtonReleased(pl::MouseButton mouseButton) {
		auto current {s_mouseButtonStates.find(mouseButton)};
		if (current == s_mouseButtonStates.end()) {
			s_mouseButtonStates[mouseButton] = false;
			s_oldMouseButtonStates[mouseButton] = false;
			return false;
		}

		auto old {s_oldMouseButtonStates.find(mouseButton)};
		if (old == s_oldMouseButtonStates.end()) {
			s_oldMouseButtonStates[mouseButton] = current->second;
			return false;
		}

		return !current->second && old->second;
	}


	bool InputManager::isRunning() {
		return s_running;
	}


	bool InputManager::wasWindowResized() {
		return s_wasWindowResized;
	}


	const pl::Vec2i &InputManager::getMousePosition() {
		return s_mousePosition;
	}


	const pl::Vec2i &InputManager::getMouseMotion() {
		return s_mouseMotion;
	}


	bool InputManager::wasMouseMoved() {
		return s_mouseMotion != pl::Vec2i(0, 0);
	}



	std::unordered_map<pl::Key, bool> InputManager::s_keyStates {};
	std::unordered_map<pl::Key, bool> InputManager::s_oldKeyStates {};
	std::unordered_map<pl::MouseButton, bool> InputManager::s_mouseButtonStates {};
	std::unordered_map<pl::MouseButton, bool> InputManager::s_oldMouseButtonStates {};
	bool InputManager::s_running {true};
	pl::Vec2i InputManager::s_mousePosition {};
	pl::Vec2i InputManager::s_mouseMotion {};
	bool InputManager::s_wasWindowResized {false};

} // namespace pl
