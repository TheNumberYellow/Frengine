#include "Server.h"

#include <iostream>
#include <stdio.h>


Server::Server() {
	
}


Server::~Server() {
}

void Server::run() {
	initSystems();

	bool running = true;

	while (running) {
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
				_players.emplace_back(tempSocket, currentID, SDL_GetTicks(), glm::vec2(0, 0));
				playerNum++;
				sprintf_s(temp, "0 %d \n", currentID);
				printf("New connection with ID %d.\n", currentID);
				currentID++;
			}
			else {
				printf("Someone tried to join the server, but it was already full :(\n");
				sprintf_s(temp, "3 \n");
			}
		}
		
		// Check for incoming data
		while (SDLNet_CheckSockets(_socketSet, 0) > 0) {
			for (unsigned int i = 0; i < _players.size(); i++) {
				if (SDLNet_SocketReady(_players[i].socket)) {
					SDLNet_TCP_Recv(_players[i].socket, temp, 1400);
					char tag = temp[0];

					switch (tag) {
					case '1':
						printf("%s\n", temp);
						SDLNet_TCP_Send(_players[i].socket, temp, strlen(temp) + 1);
						break;
					case '2':
						SDLNet_TCP_DelSocket(_socketSet, _players[i].socket);
						SDLNet_TCP_Close(_players[i].socket);
						_players.erase(_players.begin() + i);
						playerNum--;
						printf("Player with ID %d has disconnected.\n", i);
						break;
					case '3':

						break;
					}
					

				}
			}
			/*
			for (int i = 0; i < _players.size(); i++) {
				if (SDLNet_SocketReady(_players[i].socket)) {
					_players[i].timeout = SDL_GetTicks();
					SDLNet_TCP_Recv(_players[i].socket, temp, 1400);
					int num = temp[0] - '0';
					int j = 1;
					while (temp[j] >= '0' && temp[j] <= '9') {
						num *= 10;
						num += temp[j] - '0';
						j++;
					}
					if (num == 1) {
						for (int k = 0; k < _players.size(); k++) {
							if (k == i) {
								continue;
							}
							SDLNet_TCP_Send(_players[k].socket, temp, strlen(temp) + 1);
						}
					}
					else if (num == 2) {
						for (int k = 0; k < _players.size(); k++) {
							if (k == i) {
								continue;
							}
							SDLNet_TCP_Send(_players[k].socket, temp, strlen(temp) + 1);
						}
						SDLNet_TCP_DelSocket(_socketSet, _players[i].socket);
						SDLNet_TCP_Close(_players[i].socket);
						_players.erase(_players.begin() + i);
						playerNum--;
					}
				}
			}
			*/
		}
		

		// Send player positions

		
		// player timeout
		/*
		for (int i = 0; i < _players.size(); i++) {
			if (SDL_GetTicks() - _players[i].timeout > 5000) {
				for (int k = 0; k < _players.size(); k++) {
					sprintf_s(temp, "2 %d \n", _players[i].id);
					SDLNet_TCP_Send(_players[k].socket, temp, strlen(temp) + 1);
				}
				SDLNet_TCP_DelSocket(_socketSet, _players[i].socket);
				SDLNet_TCP_Close(_players[i].socket);
				_players.erase(_players.begin() + i);
				playerNum--;
			}
		}
		*/
		SDL_Delay(1);
	}
	
	
	deInitSystems();
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

void Server::addConnection(TCPsocket newSocket) {
	if (playerNum < MAX_PLAYERS) {
		SDLNet_TCP_AddSocket(_socketSet, newSocket);
		_players.emplace_back(newSocket, currentID, SDL_GetTicks(), glm::vec2(0, 0));
		playerNum++;
		sprintf_s(temp, "0 %d \n", currentID);
		printf("New connection with ID %d.\n", currentID);
		currentID++;
	}
	else {
		printf("Someone tried to join the server, but it was already full :(\n");
		sprintf_s(temp, "3 \n");
	}
}
