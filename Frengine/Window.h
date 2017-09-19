#pragma once
#include <SDL2\SDL.h>
#include <GL\glew.h>

#include <string>

namespace FR {
	class Window {
	public:
		Window();
		~Window();

		void create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
		void swapBuffer();
		
		void clear();
		void clear(GLuint bufferBit);

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }

		SDL_Window* getWindow();

	private:
		SDL_Window* _window;
		int _screenWidth, _screenHeight;
	};
}
