#pragma once

#include <SDL_net.h>
#include <SDL2\SDL.h>

#define SERVER_PORT 839

class Client {
public:
	Client();
	~Client();

	void run();
private:
	IPaddress serverIP;
	TCPsocket serverSocket;

	void initSystems();
	void deInitSystems();

	SDL_Thread* receiveThread;

	char buffer[400];
	bool running;
};

