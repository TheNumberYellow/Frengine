#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>
#include <Frengine\Camera2D.h>
#include <Frengine\Timer.h>
#include <Frengine\Keyboard.h>


#include "Tilemap.h"

#include <Windows.h>

struct Player {
	glm::vec2 playerPos = glm::vec2(0, 0);
	glm::vec2 playerSpeed = glm::vec2(0, 0);
	FR::Sprite playerSprite;
	void update(double delta) {
		playerPos += (float)delta * playerSpeed;
		playerSprite.setPos(playerPos);
	}
	void draw(FR::ShaderProgram* shader) {
		playerSprite.draw(shader);
	}
};
struct camera {
	glm::vec2 camSpeed = glm::vec2(0, 0);
};

int main(int argc, char** argv) {
	FR::Window window;
	FR::Keyboard keyboard;

	camera cam;
	Player player;

	window.create("Spinny", 800, 800, SDL_WINDOW_RESIZABLE, FR::Colour(0, 0, 0));
	
	std::vector<FR::Texture2D*> tileTextures;
	
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/blueTile.png", "blueTile"));
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/redTile.png", "redTile"));
	tileTextures.push_back(FR::ResourceManager::loadTexture("Images/greenTile.png", "greenTile"));
 
	Tilemap map;

	std::vector<int> tiles = {
		0, 1, 1, 0,
		1, 2, -1, 1,
		1, -1, 2, 1,
		0, 1, 1, 0
	};

	map.create(tileTextures, tiles, 4, 4);

	player.playerSprite.create(glm::vec2(0, 0), glm::vec2(20, 20), 0.0f, FR::ResourceManager::loadTexture("Images/player.png", "player"));


	FR::ShaderProgram* shader0 = FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	FR::Camera2D camera;
	camera.attach(shader0);

	glm::mat4 projectionMatrix = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f);

	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);

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

			}
		}
		
		double delta = timer.getDeltaTime();
		
		if (keyboard.isPressed(FR::K_UP)) {
			player.playerPos.y += 100 * delta;
		}
		else if (keyboard.isPressed(FR::K_DOWN)) {
			player.playerPos.y -= 100 * delta;
		}
		if (keyboard.isPressed(FR::K_LEFT)) {
			player.playerPos.x -= 100 * delta;
		}
		else if (keyboard.isPressed(FR::K_RIGHT)) {
			player.playerPos.x += 100 * delta;
		}

		camera.moveCam(cam.camSpeed * (float)delta);
		player.update(delta);

		window.clear();
		camera.update();

		// BEGIN DRAW

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