#include "Client.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\perpendicular.hpp>


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

	initWindow();



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
					mySpeed.x = -0.05;
					break;
				case SDLK_RIGHT:
					mySpeed.x = 0.05;
					break;
				case SDLK_UP:
					mySpeed.y = 0.05;
					break;
				case SDLK_DOWN:
					mySpeed.y = -0.05;
					break;
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w:
					forwardSpeed = 0.1f;
					break;
				case SDLK_s:
					forwardSpeed = -0.1f;
					break;
				case SDLK_a:
					strafeSpeed = -0.1f;
					break;
				case SDLK_d:
					strafeSpeed = 0.1f;
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

				case SDLK_w:
				case SDLK_s:
					forwardSpeed = 0.0f;
					break;
				case SDLK_a:
				case SDLK_d:
					strafeSpeed = 0.0f;
					break;
				}
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_FOCUS_LOST:
					_hasFocus = false;
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					_hasFocus = true;
					break;
				}
			}	
		}

		myPosition += mySpeed;
		me.setPos(myPosition);

		// Send  position to server
		sprintf_s(buffer, "1 %f %f %f", myPosition.x, myPosition.y, me.getRot());
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
						float posX, posY, rotation;					// If it's not even supposed to be getting the message in the first place there's a good chance that this is a problem that only exists when using multiple clients on the same machine.
						int ID, current;
						sscanf_s(buffer + position, " %d %f %f %f %n", &ID, &posX, &posY, &rotation, &current);

						if (players.find(ID) == players.end()) {
							FR::Sprite newSprite;
							printf("Creating sprite at X: %f Y: %f\n", posX, posY);
							newSprite.create(glm::vec2(posX, posY), glm::vec2(1, 1), rotation, pawnTexture);
							players[ID] = newSprite;
						}
						else {
							players[ID].setPos(glm::vec2(posX, posY));
							players[ID].setRot(rotation);
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

		if (_hasFocus) {
			int mouseX, mouseY;

			SDL_PumpEvents();
			SDL_GetMouseState(&mouseX, &mouseY);


			SDL_WarpMouseInWindow(window.getWindow(), _screenWidth / 2, _screenWidth / 2);

			int mouseMoveX = (_screenWidth / 2) - mouseX;
			int mouseMoveY = (_screenHeight / 2) - mouseY;

			// Move X
			camera.setCamFront(glm::rotate(camera.getCamFront(), glm::radians(0.1f * mouseMoveX), camera.getCamUp()));

			// Move Y
			glm::vec3 perpVec = glm::cross(camera.getCamFront(), camera.getCamUp());
			camera.setCamFront(glm::rotate(camera.getCamFront(), glm::radians(0.1f * mouseMoveY), perpVec));

			// Move cam pos
			camera.setCamPos(camera.getCamPos() + (forwardSpeed * camera.getCamFront()));
			camera.setCamPos(camera.getCamPos() + glm::normalize(glm::cross(camera.getCamFront(), camera.getCamUp())) * strafeSpeed);
		}
		camera.update();

		board.draw(shader0);

		for (auto it = players.begin(); it != players.end(); it++) {
			it->second.draw(shader0);
		}
		
		me.setRot(me.getRot() + 0.1);
		
		me.draw(shader0);
		testMesh.draw(shader0);

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
	SDL_Init(SDL_INIT_EVERYTHING);
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
	window.create("Online", _screenWidth, _screenHeight, NULL);
	FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	shader0 = FR::ResourceManager::getShader("shader0");

	glm::mat4 projectionMatrixOrtho = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	glm::mat4 projectionMatrixPerspective = glm::perspective(glm::radians(45.0f), (float)_screenWidth / (float)_screenHeight, 0.1f, 10000.0f);
	
	glm::mat4 projectionMatrix = projectionMatrixPerspective * projectionMatrixOrtho;
	//projectionMatrix = projectionMatrixP * projectionMatrix;

	shader0->use();
	shader0->setUniformMat4("projection", projectionMatrixPerspective);

	camera.attach(shader0);
	camera.setCamPos(glm::vec3(4.0, 4.0, 9.6));

	FR::ResourceManager::loadTexture("Images/Chess_Board.png", "board");
	FR::ResourceManager::loadTexture("Images/White_Pawn.png", "pawn");
	FR::ResourceManager::loadTexture("Images/Black_Pawn.png", "blackPawn");

	boardTexture = FR::ResourceManager::getTexture("board");
	pawnTexture = FR::ResourceManager::getTexture("pawn");
	blackPawnTexture = FR::ResourceManager::getTexture("blackPawn");

	myPosition.x = 0;
	myPosition.y = 0;

	me.create(myPosition, glm::vec2(1, 1), 0, pawnTexture);
	board.create(glm::vec2(0, 0), glm::vec2(8, 8), 0, boardTexture);

	SDL_SetWindowGrab(window.getWindow(), SDL_TRUE);
	SDL_WarpMouseInWindow(window.getWindow(), _screenWidth / 2, _screenHeight / 2);
	SDL_ShowCursor(SDL_DISABLE);

	playerInfo.vertices = new GLfloat[20]{
		// Positions			// Tex Coords
		0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		1.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,	1.0f,	1.0f,
		0.0f,	1.0f,	0.0f,	0.0f,	1.0f
	};
	playerInfo.elements = new GLuint[6]{
		0, 1, 2,
		2, 3, 0
	};

	
	testMesh.create(playerInfo, 20, 6, glm::vec3(2.0f, 2.0f, 1.0f), glm::vec3(4.0f, 4.0f, 4.0f), 0, 0, 0, pawnTexture);

	//glEnable(GL_DEPTH_TEST);
}
