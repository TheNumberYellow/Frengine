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

void Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags, Colour clearColour) {
	SDL_Init(SDL_INIT_EVERYTHING);

	unsigned int flags = SDL_WINDOW_OPENGL | windowFlags;

	_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);


	if (_window == nullptr) {
		fatalError("SDL Window could not be created.");
	}

	// Set up OpenGL context
	glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("GL Context could not be created.");
	}

	// Set up GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW initialization error.");
	}

#if _DEBUG
	//Check OpenGL version
	std::printf("~~~ Open GL Version: %s ~~~\n", glGetString(GL_VERSION));
#endif

	// Set clear colour
	glClearColor(clearColour.r, clearColour.g, clearColour.b, 1.0f);

	// Set blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	// TODO: vsync
	SDL_GL_SetSwapInterval(0);
}


void Window::swapBuffer() {
	SDL_GL_SwapWindow(_window);
}

void FR::Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::clear(GLuint bufferBit) {
	glClear(bufferBit);
}

void FR::Window::setWindowSize(int width, int height) {
	_screenWidth = width;
	_screenHeight = height;
	SDL_SetWindowSize(_window, width, height);
	glViewport(0, 0, width, height);
}

void FR::Window::setWindowTitle(std::string newTitle)
{
	SDL_SetWindowTitle(_window, newTitle.c_str());
}

SDL_Window* FR::Window::getWindow() {
	return _window;
}
