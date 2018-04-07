#pragma once
#include <SDL2\SDL.h>

#include <map>

namespace FR {
	enum Key {
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT
	};

	class Keyboard {
	
	public:
		void update(SDL_Event event);
		bool isPressed(Key key);
	private:
		std::map<Key, bool> _keyboard;
	};
}

