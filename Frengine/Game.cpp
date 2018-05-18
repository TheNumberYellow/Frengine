#include "Game.h"

#include <iostream>

using namespace FR;

Game::Game() {
}


Game::~Game() {
}

int FR::Game::RunGame() {
	Initialize();

	timer.initTimer();
	return GameLoop();
}

void FR::Game::AddDrawableElement(Drawable* drawable, ShaderProgram* shader, std::string name)
{
	GameElement newElement;
	newElement.drawable = drawable;
	newElement.shader = shader;

	elements[name] = newElement;
}

void FR::Game::AddDrawableElement(Drawable* drawable, std::string name)
{
	GameElement newElement;
	newElement.drawable = drawable;
	newElement.shader = ResourceManager::getDefaultShader();

	elements[name] = newElement;
}

Drawable* FR::Game::GetDrawable(std::string name)
{
	auto it = elements.find(name);

	if (it != elements.end()) {
		return it->second.drawable;
	}
	else {
		return nullptr;
	}

}

bool FR::Game::IsKeyPressed(FR::Key key)
{
	return keyboard.isPressed(key);
}

void FR::Game::SetWindowSize(int x, int y)
{
	window.setWindowSize(x, y);
	camera.setCamSize(glm::vec2(x, y));
}

void FR::Game::SetWindowTitle(std::string title)
{
	window.setWindowTitle(title);
}

void FR::Game::Initialize()
{
	window.create("Default Window Title", 400, 400, 0);
	
	camera.attach(ResourceManager::getDefaultShader());
	camera.setCamSize(glm::vec2(400, 400));


	SetUp();
}

int FR::Game::GameLoop() {
	while (gameRunning) {

		PollEvents();
		
		Update(timer.getDeltaTime());
		DrawElements();
		//TODO: Get any errors, return
	}
	return 0;
}

void FR::Game::DrawElements() {
	window.clear();
	camera.update();

	for (auto i = elements.begin(); i != elements.end(); i++) {
		//elements[i].drawable->draw(elements[i].shader);
		i->second.drawable->draw(i->second.shader);
	}
	window.swapBuffer();
}

void FR::Game::PollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keyboard.update(event);
		
		switch (event.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_KEYDOWN:
			KeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			KeyUp(event.key.keysym.sym);
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SetWindowSize(event.window.data1, event.window.data2);
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseClicked(event.motion.x, event.motion.y);
			break;
		}
	}
}

void FR::Game::KeyDown(SDL_Keycode keycode)
{
}

void FR::Game::KeyUp(SDL_Keycode keycode)
{
}

void FR::Game::MouseClicked(int x, int y)
{
}
