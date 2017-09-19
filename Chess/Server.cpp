#include "Server.h"

#include <iostream>
#include <stdio.h>
#include <string>

Server::Server() {

}

Server::~Server() {

}

void Server::run() {
	initSystems();

	bool running = true;
	while (running) {
		unsigned int frameStartTime = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}

		// Check for new connections
		TCPsocket tempSocket = SDLNet_TCP_Accept(_serverSocket);
		if (tempSocket) {
			if (playerNum < MAX_PLAYERS) {
				SDLNet_TCP_AddSocket(_socketSet, tempSocket);
				_players.emplace_back(tempSocket, currentID, SDL_GetTicks(), glm::vec2(0, 0), 0);
				playerNum++;
				sprintf_s(buffer, "0 %d \n", currentID);
				printf("New connection with ID %d.\n", currentID);
				currentID++;
			}
			else {
				printf("Someone tried to join the server, but it was already full :(\n");
				sprintf_s(buffer, "3 \n");
			}
		}

		// Receive position packets
		if (SDLNet_CheckSockets(_socketSet, 0)) {
			for (int i = playerNum - 1; i >= 0; i--) {
				if (SDLNet_SocketReady(_players[i].socket)) {
					
					if (SDLNet_TCP_Recv(_players[i].socket, buffer, BUFFER_SIZE) <= 0) {
						_players.erase(_players.begin() + i);
						playerNum--;
					}
					else {
						float posX, posY, rotate;
						sscanf_s(buffer, "1 %f %f %f", &posX, &posY, &rotate);
						_players[i].position = glm::vec2(posX, posY);
						_players[i].rotation = rotate;
					}
				}
			}
		}

		// Send position packets
		for (unsigned int i = 0; i < playerNum; i++) {		
			printf("Player ID: %d Position X: %f Position Y: %f Rotation: %f\n", _players[i].id, _players[i].position.x, _players[i].position.y, _players[i].rotation);
			// Clear buffer
			buffer[0] = 0;

			// Send number of other players
			sprintf_s(buffer, "%d", playerNum - 1);

			for (unsigned int j = 0; j < playerNum; j++) {
				if (i != j) {
					char playerInfo[BUFFER_SIZE];
					sprintf_s(playerInfo, " %d %f %f %f ", _players[j].id, _players[j].position.x, _players[j].position.y, _players[j].rotation);
					strcat_s(buffer, playerInfo);
				}
			}  

			//printf("Sending to user: %d packet: %s\n", _players[i].id, buffer);

			SDLNet_TCP_Send(_players[i].socket, buffer, strlen(buffer) + 1);
			
		}
		
		unsigned int frameEndTime = SDL_GetTicks();

		unsigned int frameTime = frameEndTime - frameStartTime;

		//printf("Frame Time: %d\n", frameTime);

		if (frameTime < 17) {
			SDL_Delay(17 - frameTime);
		}
	}
}

void Server::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

	SDLNet_ResolveHost(&ip, NULL, SERVER_PORT);
	_serverSocket = SDLNet_TCP_Open(&ip);

	_socketSet = SDLNet_AllocSocketSet(MAX_PLAYERS);

}

void Server::deInitSystems() {

	for (unsigned int i = 0; i < _players.size(); i++) {
		SDLNet_TCP_Close(_players[i].socket);
	}

	SDLNet_FreeSocketSet(_socketSet);
	SDLNet_TCP_Close(_serverSocket);
	SDLNet_Quit();
	SDL_Quit();
}