#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>


#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <ctime>

int main(int argc, char** argv) {

	FR::Window window;
	
	window.create("TestFrengine", 1600, 1200, NULL);

	FR::Texture2D* texture0 = FR::ResourceManager::loadTexture("Images/testImage0.png", "testImage0");
	FR::Texture2D* texture1 = FR::ResourceManager::loadTexture("Images/testImage1.png", "testImage1");
	FR::Texture2D* texture2 = FR::ResourceManager::loadTexture("Images/testImage2.png", "testImage2");
	FR::Texture2D* texture3 = FR::ResourceManager::loadTexture("Images/testImage3.png", "testImage3");

	FR::ShaderProgram* shader0 = FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");

	FR::Sprite sprite0(glm::vec2(0, 0), glm::vec2(800, 600), 0, texture0);

	FR::Sprite sprite1(glm::vec2(800, 0), glm::vec2(800, 600), 0, texture1);
	
	FR::Sprite sprite2(glm::vec2(800, 600), glm::vec2(800, 600), 0, texture2);
	
	FR::Sprite sprite3(glm::vec2(0, 600), glm::vec2(800, 600), 0, texture3);

	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1600.0f, 0.0f, 1200.0f);

	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);


	bool running = true;
	while (running) {
		std::clock_t start;
		double duration;
		start = std::clock();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		window.clear();
		
		sprite0.setRot(sprite0.getRot() + 0.01);

		// DRAW
		sprite0.draw(shader0);
		sprite1.draw(shader0);
		sprite2.draw(shader0);
		sprite3.draw(shader0);
		// END DRAW

		window.swapBuffer();

		sprite3.setPos(sprite3.getPos() + glm::vec2(1, 0));

		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		std::cout << "Duration: " << duration << "\n";
	}

	FR::ResourceManager::unuseShader();
	FR::ResourceManager::unbindTexture();
	
	return 0;
}