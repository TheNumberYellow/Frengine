#pragma once

#include <SDL_net.h>
#include <SDL2\SDL.h>

#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>
#include <Frengine\Camera2D.h>
#include <Frengine\Camera3D.h>
#include <Frengine\Mesh.h>

#include <map>

#define SERVER_PORT 8392
#define BUFFER_SIZE 1400

#define PI 3.14159265359

class Client {
public:
	Client();
	~Client();
	
	void run();
private:
	void initSystems();
	void deInitSystems();
	void initWindow();

	IPaddress serverIP;
	TCPsocket serverSocket;
	SDLNet_SocketSet socketSet;

	FR::Window window;
	FR::ShaderProgram* shader0;
	FR::Camera3D camera;

	std::map<int, FR::Mesh> players;
	std::map<int, FR::Mesh> mPlayers;


	GLfloat forwardSpeed = 0;
	GLfloat strafeSpeed = 0;

	glm::vec2 myPosition;
	glm::vec2 mySpeed;
	FR::Mesh me;
	FR::Sprite board;

	FR::Mesh testMesh;
	FR::Mesh* woodMesh;

	FR::Mesh meshy;

	FR::Texture2D* boardTexture;
	FR::Texture2D* pawnTexture;
	FR::Texture2D* blackPawnTexture;
	FR::Texture2D* woodTexture;
	FR::Texture2D* metalTexture;


	char buffer[BUFFER_SIZE];
	bool running = true;

	FR::VerticesInfo playerInfo;

	bool _hasFocus = false;
	bool _spacePressed = false;

	int _screenWidth = 800;
	int _screenHeight = 800;
};