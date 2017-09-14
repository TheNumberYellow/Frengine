#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL_net.h>
#include <SDL2\SDL.h>

#include <glm\glm.hpp>

#define MAX_PLAYERS 10
#define TIMEOUT_LIMIT 5000
#define SERVER_PORT 839

struct Player {
	TCPsocket socket;
	int id;
	Uint32 timeout;
	glm::vec2 position;
	Player(TCPsocket _socket, int _id, Uint32 _timeout, glm::vec2 _position) : socket(_socket), timeout(_timeout), id(_id), position(_position) {}
};

class Server {
public:
	Server();
	~Server();

	void run();

private:
	void initSystems();
	void deInitSystems();

	void addConnection(TCPsocket newSocket);


	std::vector<Player> _players;
	TCPsocket _serverSocket;
	IPaddress ip;

	SDLNet_SocketSet _socketSet;

	Uint32 _timeout;

	int currentID = 0;
	int playerNum = 0;

	char temp[1400];
};

