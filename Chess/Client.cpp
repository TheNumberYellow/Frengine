#include "Client.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

Client::Client() {

}

Client::~Client() {

}

void Client::run() {

	initSystems();

	std::string ipStr;

	std::string input;

	printf("Enter IP address to connect to:\n");
	std::getline(std::cin, ipStr);

	if (SDLNet_ResolveHost(&serverIP, ipStr.c_str(), SERVER_PORT) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		deInitSystems();
		return;
	}

	serverSocket = SDLNet_TCP_Open(&serverIP);
	
	if (!serverSocket) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		deInitSystems();
		return;
	}

	if (SDLNet_TCP_AddSocket(socketSet, serverSocket) == -1) {
		printf("SDLNet_TCP_AddSocet: %s\n", SDLNet_GetError());
		deInitSystems();
		return;
	}

	//initWindow();

	while (running) {
		
		unsigned int frameStartTime = SDL_GetTicks();
		// Take input
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				deInitSystems();
				return;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					mySpeed.x = -5;
					break;
				case SDLK_RIGHT:
					mySpeed.x = 5;
					break;
				case SDLK_UP:
					mySpeed.y = 5;
					break;
				case SDLK_DOWN:
					mySpeed.y = -5;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					mySpeed.x = 0;
					break;
				case SDLK_RIGHT:
					mySpeed.x = 0;
					break;
				case SDLK_UP:
					mySpeed.y = 0;
					break;
				case SDLK_DOWN:
					mySpeed.y = 0;
					break;
				}
			}	
		}

		myPosition += mySpeed;
		me.setPos(myPosition);

		// Send  position to server
		sprintf_s(buffer, "1 %d %d", (int)myPosition.x, (int)myPosition.y);
		SDLNet_TCP_Send(serverSocket, buffer, strlen(buffer) + 1);


		// Receive data
		if (SDLNet_CheckSockets(socketSet, 0)) {
			if (SDLNet_SocketReady(serverSocket)) {
				if (SDLNet_TCP_Recv(serverSocket, buffer, BUFFER_SIZE) <= 0) {
					printf("SDLNet_TCP_Recv: %s\nServer likely disconnected.\n", SDLNet_GetError());
					deInitSystems();
					return;
				}

				int numOtherPlayers, position;
				SDLNet_TCP_Recv(serverSocket, buffer, BUFFER_SIZE);
				
				//printf("Recieved Buffer: %s\n", buffer);
				sscanf_s(buffer, "%d%n", &numOtherPlayers, &position);

				if (numOtherPlayers > 0 && numOtherPlayers < 10) {	// TODO: figure out why when first connecting client receives tail end of another tcp packet... test if this is only when using same computer for client + server etc.
					for (int i = 0; i < numOtherPlayers; i++) {		// Good thing to test next is which packet it's actually getting the tail end of - ie. is it getting the end of a packet it's actually supposed to be getting in the first place?
						int ID, posX, posY, current;				// If it's not even supposed to be getting the message in the first place there's a good chance that this is a problem that only exists when using multiple clients on the same machine.
						sscanf_s(buffer + position, " %d %d %d %n", &ID, &posX, &posY, &current);

						if (players.find(ID) == players.end()) {
							FR::Sprite newSprite;
							newSprite.create(glm::vec2(posX, posY), glm::vec2(100, 100), 0, pawnTexture);
							players[ID] = newSprite;
						}
						else {
							players[ID].setPos(glm::vec2(posX, posY));
						}

						position += current;
					}
				}
				else if (numOtherPlayers >= 10) {
					printf("Received fragment packet: %s\n", buffer);
				}
			}
		}
		
		// Draw
		window.clear();

		//glm::vec3 _cameraPosition(glm::vec3(0.0, 0.0, 3.0));
		//glm::vec3 _cameraFront(glm::vec3(0.0, 0.0, -1.0));
		//glm::vec3 _cameraUp(glm::vec3(0.0, 1.0, 0.0));
		
		//glm::mat4 view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraFront, _cameraUp);

		//shader0->setUniformMat4("view", view);

		//camera.update();

		board.draw(shader0);

		for (auto it = players.begin(); it != players.end(); it++) {
			it->second.draw(shader0);
		}
		
		me.setRot(me.getRot() + 0.01);
		
		me.draw(shader0);

		window.swapBuffer();

		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();
		
		unsigned int frameEndTime = SDL_GetTicks();

		unsigned int frameTime = frameEndTime - frameStartTime;

		//printf("Frame time: %d\n", frameTime);

		if (frameTime < 17) {
			SDL_Delay(17 - frameTime);
		}
		
	}
	deInitSystems();
}

void Client::initSystems() {
	//SDL_Init(SDL_INIT_EVERYTHING);
	initWindow();
	SDLNet_Init();

	socketSet = SDLNet_AllocSocketSet(1);
}

void Client::deInitSystems() {
	SDLNet_Quit();
	SDL_Quit();

	SDLNet_TCP_Close(serverSocket);

	SDLNet_FreeSocketSet(socketSet);
}

void Client::initWindow() {
	window.create("Online", 800, 800, NULL);
	FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	shader0 = FR::ResourceManager::getShader("shader0");

	glm::mat4 projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);
	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrix);

	//camera.attach(shader0);

	FR::ResourceManager::loadTexture("Images/Chess_Board.png", "board");
	FR::ResourceManager::loadTexture("Images/White_Pawn.png", "pawn");

	boardTexture = FR::ResourceManager::getTexture("board");
	pawnTexture = FR::ResourceManager::getTexture("pawn");

	me.create(glm::vec2(0, 0), glm::vec2(100, 100), 0, pawnTexture);
	board.create(glm::vec2(0, 0), glm::vec2(800, 800), 0, boardTexture);
}
