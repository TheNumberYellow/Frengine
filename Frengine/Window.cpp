#include "Window.h"
#include "Errors.h"

using namespace FR;

Window::Window() :
	_window(nullptr)
{
}


Window::~Window() {
	SDL_DestroyWindow(_window);
}

void Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags) {
	SDL_Init(SDL_INIT_EVERYTHING);

	unsigned int flags = SDL_WINDOW_OPENGL | windowFlags;

	_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created.");
	}

	// Set up OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL GL Context could not be created.");
	}

	// Set up GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW initialization error.");
	}

	//Check OpenGL version
	std::printf("~~~ Open GL Version: %s ~~~\n", glGetString(GL_VERSION));

	// Set clear colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Set blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}


void Window::swapBuffer() {
	SDL_GL_SwapWindow(_window);
}

void Window::clear(GLuint bufferBit) {
	glClear(bufferBit);
}
