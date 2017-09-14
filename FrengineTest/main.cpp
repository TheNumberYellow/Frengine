#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>

#include "Server.h"
#include "Client.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int main(int argc, char** argv) {

	//printf("Size of Char: %u\n", sizeof(char));
	//printf("Size of glm::vec2: %u\n", sizeof(glm::vec2));
	//printf("Size of float: %u\n", sizeof(float));



	std::string input;
	do {
		printf("Client(c) or Server(s)?\n");
		std::getline(std::cin, input);
	} while (input != "c" && input != "s");

	if (input == "c") {
		Client client;
		client.run();
	}
	else {
		Server server;
		server.run();
	}

	printf("Enter anything to quit.\n");
	int n;
	std::cin >> n;

	return 0;
	

	/*
	FR::Window window;
	
	window.create("TestFrengine", 1600, 1200, NULL);

	FR::ResourceManager::loadTexture("Images/testImage0.png", "testImage0");
	FR::ResourceManager::loadTexture("Images/testImage1.png", "testImage1");
	FR::ResourceManager::loadTexture("Images/testImage2.png", "testImage2");
	FR::ResourceManager::loadTexture("Images/testImage3.png", "testImage3");
		
	FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");

	FR::Texture2D* texture0 = FR::ResourceManager::getTexture("testImage0");
	FR::Texture2D* texture1 = FR::ResourceManager::getTexture("testImage1");
	FR::Texture2D* texture2 = FR::ResourceManager::getTexture("testImage2");
	FR::Texture2D* texture3 = FR::ResourceManager::getTexture("testImage3");

	FR::ShaderProgram* shader0 = FR::ResourceManager::getShader("shader0");

	FR::Sprite sprite0;
	sprite0.create(glm::vec2(0, 0), glm::vec2(800, 600), texture0);

	FR::Sprite sprite1;
	sprite1.create(glm::vec2(800, 0), glm::vec2(800, 600), texture1);
	
	FR::Sprite sprite2;
	sprite2.create(glm::vec2(800, 600), glm::vec2(800, 600), texture2);
	
	FR::Sprite sprite3;
	sprite3.create(glm::vec2(0, 600), glm::vec2(800, 600), texture3); 


	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1600.0f, 0.0f, 1200.0f);

	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);


	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		window.clear();
		
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
	}

	FR::ResourceManager::unuseShader();
	FR::ResourceManager::unbindTexture();
	*/
}