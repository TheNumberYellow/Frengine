#include "Client.h"

#include <stdio.h>
#include <iostream>
#include <string>

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
		return;
	}

	serverSocket = SDLNet_TCP_Open(&serverIP);
	if (!serverSocket) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return;
	}
	
	while (true) {
		printf("Enter message to send to server, or Q to quit.\n");
		std::getline(std::cin, input);
		if (input == "Q") {
			
			sprintf_s(buffer, "2");
			SDLNet_TCP_Send(serverSocket, buffer, strlen(buffer) + 1);
			running = false;

			SDL_WaitThread(receiveThread, NULL);
			exit(0);
		}
		
		sprintf_s(buffer, "1 %s", input.c_str());
		SDLNet_TCP_Send(serverSocket, buffer, strlen(buffer) + 1);
		SDLNet_TCP_Recv(serverSocket, buffer, 1400);

		printf("Received packet: %s\n", buffer);
	}
	deInitSystems();
}

void Client::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
}

void Client::deInitSystems() {
	SDLNet_Quit();
	SDL_Quit();
}
