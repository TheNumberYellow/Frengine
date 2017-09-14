#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "Client.h"
#include "Server.h"

int main(int argc, char** argv) {


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

	printf("Press enter to quit.\n");
	getchar();
	
	return 0;

	/*
	FR::Window window;

	window.create("Chess Online", 800, 800, NULL);

	FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	FR::ShaderProgram* shader0 = FR::ResourceManager::getShader("shader0");

	FR::ResourceManager::loadTexture("Images/Chess_Board.png", "board");
	FR::Texture2D* boardTexture = FR::ResourceManager::getTexture("board");

	FR::ResourceManager::loadTexture("Images/White_Pawn.png", "wPawn");
	FR::ResourceManager::loadTexture("Images/Black_Pawn.png", "bPawn");
	FR::ResourceManager::loadTexture("Images/White_Rook.png", "wRook");
	FR::ResourceManager::loadTexture("Images/Black_Rook.png", "bRook");


	FR::Texture2D* wPawnTexture = FR::ResourceManager::getTexture("wPawn");
	FR::Texture2D* bPawnTexture = FR::ResourceManager::getTexture("bPawn");
	FR::Texture2D* wRookTexture = FR::ResourceManager::getTexture("wRook");
	FR::Texture2D* bRookTexture = FR::ResourceManager::getTexture("bRook");

	FR::Sprite pieces[20];

	for (int i = 0; i < 8; i++) {
		pieces[i].create(glm::vec2(i * 100, 100), glm::vec2(100, 100), wPawnTexture);
	}
	for (int i = 0; i < 8; i++) {
		pieces[i + 8].create(glm::vec2(i * 100, 600), glm::vec2(100, 100), bPawnTexture);
	}
	pieces[16].create(glm::vec2(0, 0), glm::vec2(100, 100), wRookTexture);
	pieces[17].create(glm::vec2(700, 0), glm::vec2(100, 100), wRookTexture);
	pieces[18].create(glm::vec2(0, 700), glm::vec2(100, 100), bRookTexture);
	pieces[19].create(glm::vec2(700, 700), glm::vec2(100, 100), bRookTexture);



	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);
	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);

	FR::Sprite boardSprite;
	boardSprite.create(glm::vec2(0, 0), glm::vec2(800, 800), boardTexture);

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

		// Draw board
		boardSprite.draw(shader0);

		for (int i = 0; i < 20; i++) {
			pieces[i].draw(shader0);
		}

		window.swapBuffer();

		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();
	}
	*/

}