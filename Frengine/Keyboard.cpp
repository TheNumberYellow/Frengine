#include "Keyboard.h"

using namespace FR;	

void FR::Keyboard::update(SDL_Event event) {
	if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) {
		return;
	}
	bool isPressed;
	if (event.type == SDL_KEYDOWN) {
		isPressed = true;
	}
	else {
		isPressed = false;
	}

	switch (event.key.keysym.sym) {
	case SDLK_UP:
	case SDLK_w:
		_keyboard[K_UP] = isPressed;
		break;
	case SDLK_DOWN:
	case SDLK_s:
		_keyboard[K_DOWN] = isPressed;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		_keyboard[K_LEFT] = isPressed;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		_keyboard[K_RIGHT] = isPressed;
		break;
	}
}

bool FR::Keyboard::isPressed(Key key) {
	//TODO: Initializes key-less values to false
	return _keyboard[key];
}
