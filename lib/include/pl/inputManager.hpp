#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl {
	enum class Key {
		eA = SDL_SCANCODE_A,
		eB, eC, eD, eF, eG, eH, eI, eJ, eK, eL, eM, eN, eO, eP, eQ, eR, eS, eT, eU, eV, eW, eX, eY, eZ,
		e1 = SDL_SCANCODE_1,
		e2, e3, e4, e5, e6, e7, e8, e9, e0,

		eEscape = SDL_SCANCODE_ESCAPE,
		eTab = SDL_SCANCODE_TAB,
		eLShift = SDL_SCANCODE_LSHIFT,
		eLCtrl = SDL_SCANCODE_LCTRL,
		eLAlt = SDL_SCANCODE_LALT,
		eSpace = SDL_SCANCODE_SPACE,
		eRAlt = SDL_SCANCODE_RALT,
		eRCtrl = SDL_SCANCODE_RCTRL,
		eRShift = SDL_SCANCODE_RSHIFT,
		eReturn = SDL_SCANCODE_RETURN,
		eBackspace = SDL_SCANCODE_BACKSPACE,

		eF1 = SDL_SCANCODE_F1,
		eF2, eF3, eF4, eF5, eF6, eF7, eF8, eF9, eF10, eF11, eF12,

		eRight = SDL_SCANCODE_RIGHT,
		eLeft = SDL_SCANCODE_LEFT,
		eDown = SDL_SCANCODE_DOWN,
		eUp = SDL_SCANCODE_UP,

		eHome = SDL_SCANCODE_HOME,
		eEnd = SDL_SCANCODE_END,
		ePageUp = SDL_SCANCODE_PAGEUP,
		ePageDown = SDL_SCANCODE_PAGEDOWN,
		eDelete = SDL_SCANCODE_DELETE
	};

	enum class MouseButton {
		eLeft = SDL_BUTTON_LEFT,
		eMiddle = SDL_BUTTON_MIDDLE,
		eRight = SDL_BUTTON_RIGHT,
		eX1 = SDL_BUTTON_X1,
		eX2 = SDL_BUTTON_X2
	};

	class PL_CORE InputManager final {
		public:
			InputManager() = delete;

			static void update();

			static bool isKeyDown(pl::Key key);
			static bool isKeyUp(pl::Key key);
			static bool wasKeyPressed(pl::Key key);
			static bool wasKeyReleased(pl::Key key);

			static bool isMouseButtonDown(pl::MouseButton mouseButton);
			static bool isMouseButtonUp(pl::MouseButton mouseButton);
			static bool wasMouseButtonPressed(pl::MouseButton mouseButton);
			static bool wasMouseButtonReleased(pl::MouseButton mouseButton);

			static bool isRunning();
			static bool wasWindowResized();

			static const pl::Vec2i &getMousePosition();
			static const pl::Vec2i &getMouseMotion();
			static bool wasMouseMoved();

		private:
			static std::unordered_map<pl::Key, bool> s_keyStates;
			static std::unordered_map<pl::Key, bool> s_oldKeyStates;
			static std::unordered_map<pl::MouseButton, bool> s_mouseButtonStates;
			static std::unordered_map<pl::MouseButton, bool> s_oldMouseButtonStates;
			static bool s_running;
			static pl::Vec2i s_mousePosition;
			static pl::Vec2i s_mouseMotion;
			static bool s_wasWindowResized;
	};

} // namespace pl
