#pragma once
#include <SDL2\SDL.h>
#include <GL\glew.h>

#include <string>

namespace FR {
	struct Colour {
		Colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
		float r, g, b;
	};

	class Window {
	public:
		Window();
		~Window();

		void create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags, Colour clearColour = Colour(1.0f, 0.078f, 0.578f));
		void swapBuffer();
		
		void clear();
		void clear(GLuint bufferBit);

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }

		void setWindowSize(int width, int height);
		void setWindowTitle(std::string newTitle);

		SDL_Window* getWindow();

	private:
		SDL_Window* _window;
		SDL_GLContext glContext;
		int _screenWidth, _screenHeight;
	};
}
