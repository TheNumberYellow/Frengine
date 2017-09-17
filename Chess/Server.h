#pragma once
#include <SDL_net.h>

#include <glm\glm.hpp>

#include <vector>

#define MAX_PLAYERS 10
#define TIMEOUT_LIMIT 5000
#define SERVER_PORT 8392
#define BUFFER_SIZE 1400

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

	int currentID = 0;
	unsigned int playerNum = 0;

	char buffer[BUFFER_SIZE];
};