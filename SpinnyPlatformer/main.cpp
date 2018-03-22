#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>
#include <Frengine\Camera2D.h>

#include "Tilemap.h"

#include <Windows.h>

int main(int argc, char** argv) {
	FR::Window window;

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

	FR::ShaderProgram* shader0 = FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	FR::Camera2D camera;
	camera.attach(shader0);

	glm::mat4 projectionMatrix = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f);

	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);

	bool running = true;
	while (running) {
		glm::vec2 camPos = camera.getCamPos();
		float camRot = camera.getCamRot();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					camera.setCamPos(glm::vec2(camPos.x, camPos.y + 10));
					break;
				case SDLK_DOWN:
					camera.setCamPos(glm::vec2(camPos.x, camPos.y - 10));
					break;
				case SDLK_LEFT:
					camera.setCamPos(glm::vec2(camPos.x - 10, camPos.y));
					break;
				case SDLK_RIGHT:
					camera.setCamPos(glm::vec2(camPos.x + 10, camPos.y));
					break;
				case SDLK_q:
					camera.setCamRot(camRot + 0.2);
					break;
				case SDLK_e:
					camera.setCamRot(camRot - 0.2);
					break;
				}
				break;

			}
		}

		window.clear();
		camera.update();
		
		// BEGIN DRAW

		map.draw(shader0);


		// END DRAW
		window.swapBuffer();

		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();

	}
	FR::ResourceManager::unuseShader();
	FR::ResourceManager::unbindTexture();
	return 0;
}