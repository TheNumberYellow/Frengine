#if 0
#include "MyGame.h"

int main(int argc, char** argv) {
	FR::Game* game = new MyGame();
	game->RunGame();

	return 0;
}

#endif

#if 1

#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>
#include <Frengine\Camera2D.h>
#include <Frengine\Timer.h>
#include <Frengine\Keyboard.h>

#include <math.h>
#include <iostream>

#include "Tilemap.h"
#include "Player.h"

#include "MyGame.h"

#include <Windows.h>

int screenWidth = 1600;
int screenHeight = 800;




struct Camera {
	glm::vec2 camSpeed = glm::vec2(0, 0);
	double rotSpeed = 0.0;
};



int main(int argc, char** argv) {
	FR::Window window;
	FR::Keyboard keyboard;

	Camera cam;
	Player player;
	
	window.create("Spinny", screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, FR::Colour(0.0 / 255.0, 191.0 / 255.0, 255.0 / 255.0));
	
	std::vector<FR::Texture2D*> tileTextures;
	
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/blueTile.png", "blueTile"));
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/redTile.png", "redTile"));
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/greenTile.png", "greenTile"));
 
	Tilemap map;

	std::vector<int> tiles = {
		2,	0,	1,	0,	1,	0,	1,	2,
		2, -1, -1, -1, -1, -1, -1,	2,
		2, -1, -1, -1, -1, -1, -1,	2,
		1,	0,  1,	0,  1,  0,  1,	1
	};

	map.create(tileTextures, tiles, 8, 4, glm::vec2(80, 80));

	player.playerSprite.create(glm::vec2(0, 0), glm::vec2(60, 60), 0.0f, FR::ResourceManager::loadTexture("Images/player.png", "player"));

	FR::Texture2D* backgroundTexture1 = FR::ResourceManager::loadTexture("Images/backgroundLayer1.png", "backgroundLayer1");
	FR::Texture2D* backgroundTexture2 = FR::ResourceManager::loadTexture("Images/backgroundLayer2.png", "backgroundLayer2");
	FR::Texture2D* backgroundTexture3 = FR::ResourceManager::loadTexture("Images/backgroundLayer3.png", "backgroundLayer3");

	FR::Sprite backgroundSprite1(glm::vec2(-400, -400), glm::vec2(screenWidth * 2, screenHeight), 0.0, backgroundTexture1);
	FR::Sprite backgroundSprite2(glm::vec2(-400, -400), glm::vec2(screenWidth * 2, screenHeight), 0.0, backgroundTexture2);
	FR::Sprite backgroundSprite3(glm::vec2(-400, -400), glm::vec2(screenWidth * 2, screenHeight), 0.0, backgroundTexture3);

	//FR::ShaderProgram* shader0 = FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	FR::ShaderProgram* shader0 = FR::ResourceManager::getDefaultShader();

	FR::Camera2D camera;
	camera.attach(shader0);

	camera.setCamSize(glm::vec2(screenWidth, screenHeight));
	
	FR::Timer timer;
	timer.initTimer();

	bool running = true;
	while (running) {
		float camRot = camera.getCamRot();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			keyboard.update(event);
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				}
				break;
			case SDL_MOUSEWHEEL:
				if (event.wheel.y < 0) {
					glm::vec2 camSize = camera.getCamSize();

					camSize.x += 100;
					camSize.y += 50;
					camera.setCamSize(camSize);
				}
				else if (event.wheel.y > 0) {
					glm::vec2 camSize = camera.getCamSize();

					camSize.x -= 100;
					camSize.y -= 50;
					camera.setCamSize(camSize);
				}
				break;
			}
		}
		
		double delta = timer.getDeltaTime();
		
		if (keyboard.isPressed(FR::K_UP)) {
			player.playerSpeed.y = 200.0;
		}
		else if (keyboard.isPressed(FR::K_DOWN)) {
			player.playerSpeed.y = -200.0;
		}
		if (keyboard.isPressed(FR::K_LEFT)) {
			player.playerSpeed.x = -200.0;
		}
		else if (keyboard.isPressed(FR::K_RIGHT)) {
			player.playerSpeed.x = 200.0;
		}

		if (keyboard.isPressed(FR::K_q)) {
			cam.rotSpeed = -M_PI;
		}
		else if (keyboard.isPressed(FR::K_e)) {
			cam.rotSpeed = M_PI;
		}
		else {
			cam.rotSpeed = 0.0;
		}

		player.playerSpeed.y -= 100.0 * delta;

		//std::cout << player.playerSpeed.y << std::endl;

		player.playerSprite.rotate(-cam.rotSpeed * delta);
		camera.rotate(cam.rotSpeed * delta);
		camera.setCamPos(player.playerPos);

		player.update(delta, map);

		window.clear();
		camera.update();

		backgroundSprite3.setPos((player.playerPos * 0.99f) - glm::vec2(screenWidth / 2, screenHeight / 2));
		backgroundSprite2.setPos((player.playerPos * 0.77f) - glm::vec2(screenWidth / 2, screenHeight / 2));
		backgroundSprite1.setPos((player.playerPos * 0.55f) - glm::vec2(screenWidth / 2, screenHeight / 2));

		// BEGIN DRAW
		backgroundSprite3.draw(shader0);
		backgroundSprite2.draw(shader0);
		backgroundSprite1.draw(shader0);

		map.draw(shader0);
		player.draw(shader0);

		// END DRAW
		window.swapBuffer();

		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();

	}
	FR::ResourceManager::unuseShader();
	FR::ResourceManager::unbindTexture();
	return 0;
}

#endif