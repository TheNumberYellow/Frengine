
#include <Frengine\Window.h>
#include <Frengine\ResourceManager.h>
#include <Frengine\Sprite.h>
#include <Frengine\Camera2D.h>
#include <Frengine\Timer.h>

#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 1200;

//const double ACCEL_RATE = 0.05;
//const double ROT_SPEED = 0.05;
//const double FIX_FORCE = 0.08;

const double ACCEL_RATE = 350.0; // Pixels/Sec/Sec
const double ROT_SPEED = 3.0; // Rads/Sec
const double FIX_FORCE = 400.0; // Pixels/Sec/Sec

struct PlayerShip {
	PlayerShip() :	pos(glm::vec2(0, 0)),
					speed(glm::vec2(0, 0)), 
					size(glm::vec2(50, 50)),
					forwardAccel(0),
					rot(0),
					rotSpeed(0),
					camMode(CameraMode::NORMAL)
	{}

	glm::vec2 pos;
	glm::vec2 speed;
	glm::vec2 size;

	double forwardAccel;
	double rot;
	double rotSpeed;

	enum class CameraMode {
		NORMAL,
		FOLLOW_ROT
	} camMode;
};

struct Planet {
	// Position is relative to Sector
	glm::vec2 pos;
	glm::vec2 size;

	FR::Sprite* planetSprite;

};

struct Sector {
	std::vector<Planet*> planets;

	FR::Sprite* backgroundSprite;

	void drawSectorBG(FR::ShaderProgram* shader) {
		backgroundSprite->draw(shader);
	}

	void drawSectorPlanets(FR::ShaderProgram* shader) {
		for (unsigned int i = 0; i < planets.size(); i++) {
			planets[i]->planetSprite->draw(shader);
		}
	}

	void drawSector(FR::ShaderProgram* shader) {
		drawSectorBG(shader);
		drawSectorPlanets(shader);
	}
};

struct Universe {
	int sectorCountX;
	int sectorCountY;

	glm::vec2 sectorSize;

	std::vector<Sector*> sectors;
};

float projectionWidth = 2000.0f;
float projectionHeight = 2000.0f;

std::map<std::string, bool> playerKeyboard;


int numTicksSampled = 0;	// Misleading
double secondTimer = 0;		// Variable
double fpsCounter = 0;		// Names

bool holdingTab = false;

void printFPS(double deltaSecs) {
	secondTimer += deltaSecs;
	fpsCounter += 1 / deltaSecs;
	numTicksSampled++;

	if (secondTimer > 1) {
		secondTimer -= 1;
		fpsCounter /= numTicksSampled;
		numTicksSampled = 0;

		std::cout << "FPS: " << fpsCounter << "\n";
		fpsCounter = 0;
	}
}

void resizeWindow(int width, int height, FR::ShaderProgram* shader, FR::Window* window) {
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

int main(int argc, char** argv) {

	FR::Timer::initTimer();
	
	// Set up player variables

	PlayerShip player;
	player.size = glm::vec2(40, 40);

	// Set up window, textures, sprites, shader, camera
	FR::Window window;

	window.create("Platformer", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	FR::Texture2D* space = FR::ResourceManager::loadTexture("Images/space.jpg", "space");
	FR::Texture2D* blueSpace = FR::ResourceManager::loadTexture("Images/blueSpace.png", "blueSpace");
	
	FR::Texture2D* playerShip = FR::ResourceManager::loadTexture("Images/PlayerShip.png", "playerShip");
	FR::Sprite shipSprite(player.pos - (player.size * 0.5f), player.size, player.rot, playerShip);

	FR::Texture2D* planet0 = FR::ResourceManager::loadTexture("Images/orangePlanet.png", "planet0");

	// Set up Universe
	Universe universe;
	universe.sectorCountX = 16;
	universe.sectorCountY = 16;
	universe.sectorSize = glm::vec2(4000, 4000);

	for (int i = 0; i < universe.sectorCountX * universe.sectorCountY; i++) {
		int sectorLocationX = i % universe.sectorCountX;
		int sectorLocationY = i / universe.sectorCountX;

		glm::vec2 globalSectorOffset = glm::vec2(sectorLocationX * universe.sectorSize.x, sectorLocationY * universe.sectorSize.y);

		Sector* newSector = new Sector();
		for (int i = 0; i < 2; i++) {
			Planet* newPlanet = new Planet();

			newPlanet->pos = glm::vec2(std::rand() % (int)universe.sectorSize.x, std::rand() % (int)universe.sectorSize.y);
			newPlanet->size = glm::vec2(400, 400);

			// TODO: For now, planets are being drawn from corner
			newPlanet->planetSprite = new FR::Sprite(globalSectorOffset + newPlanet->pos, newPlanet->size, 0.0, FR::ResourceManager::getTexture("planet0"));
			newSector->planets.push_back(newPlanet);
		}

		newSector->backgroundSprite = new FR::Sprite(globalSectorOffset, universe.sectorSize, 0, FR::ResourceManager::getTexture("space"));

		universe.sectors.push_back(newSector);
	}

	FR::ShaderProgram* shader0 = FR::ResourceManager::loadShaderProgram("Shaders/testShader.vert", "Shaders/testShader.frag", "shader0");
	FR::Camera2D camera;
	camera.attach(shader0);
	
	camera.setCamSize(glm::vec2(projectionWidth, projectionHeight));

	bool running = true;
	while (running) {		
		double deltaSecs = FR::Timer::getDeltaTime();

		printFPS(deltaSecs);
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_UP:
				case SDLK_w:
					playerKeyboard["UP"] = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					playerKeyboard["LEFT"] = true; 
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					playerKeyboard["RIGHT"] = true;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerKeyboard["DOWN"] = true;
					break;
				case SDLK_SPACE:
					playerKeyboard["SPACE"] = true;
					break;
				case SDLK_LSHIFT:
					playerKeyboard["SHIFT"] = true;
					break;
				case SDLK_TAB:
					playerKeyboard["TAB"] = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					playerKeyboard["UP"] = false;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					playerKeyboard["LEFT"] = false;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					playerKeyboard["RIGHT"] = false;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					playerKeyboard["DOWN"] = false;
					break;
				case SDLK_SPACE:
					playerKeyboard["SPACE"] = false;
					break;
				case SDLK_LSHIFT:
					playerKeyboard["SHIFT"] = false;
					break;
				case SDLK_TAB:
					playerKeyboard["TAB"] = false;
					break;
				}
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					resizeWindow(event.window.data1, event.window.data2, shader0, &window);
					std::cout << "Window Width: " << event.window.data1 << " Window Height" << event.window.data2 << "\n";
					break;

				}
				break;
			case SDL_MOUSEWHEEL:
				if (event.wheel.y < 0 && projectionWidth < 8000) {
					projectionWidth += 100;
					projectionHeight += 100;

					camera.setCamSize(glm::vec2(projectionWidth, projectionHeight));
				}
				else if (event.wheel.y > 0 && projectionWidth > 200) {
					projectionWidth -= 100;
					projectionHeight -= 100;

					camera.setCamSize(glm::vec2(projectionWidth, projectionHeight));
				}
				break;
			}
		}
		if (playerKeyboard["UP"]) {
			if (playerKeyboard["SHIFT"]) {
				player.forwardAccel = ACCEL_RATE * 2;
			}
			else {
				player.forwardAccel = ACCEL_RATE;
			}
		}
		else {
			player.forwardAccel = 0;
		}

		if (playerKeyboard["LEFT"] && playerKeyboard["RIGHT"]) {
			// Do nothing
		}
		else if (playerKeyboard["LEFT"]) {
			if (playerKeyboard["UP"]) {
				player.rotSpeed = (ROT_SPEED / 2) * deltaSecs;
			}
			else {
				player.rotSpeed = (ROT_SPEED) * deltaSecs;
			}
		}
		else if (playerKeyboard["RIGHT"]) {
			if (playerKeyboard["UP"]) {
				player.rotSpeed = (-ROT_SPEED / 2) * deltaSecs;
			}
			else {
				player.rotSpeed = (-ROT_SPEED) * deltaSecs;
			}
		}
		else {
			player.rotSpeed = 0;
		}

		if (playerKeyboard["SPACE"]) {
				glm::vec2 fixVector = -player.speed;
				fixVector = glm::normalize(fixVector);
				fixVector *= FIX_FORCE * deltaSecs;
			
			if (glm::length(player.speed) > (0.1 * deltaSecs)) {
				player.speed += fixVector;
			}
			else {
				player.speed = glm::vec2(0, 0);
			}
		}

		if (playerKeyboard["TAB"] && !holdingTab) {
			if (player.camMode == PlayerShip::CameraMode::NORMAL) {
				player.camMode = PlayerShip::CameraMode::FOLLOW_ROT;
			}
			else {
				player.camMode = PlayerShip::CameraMode::NORMAL;
			}
			holdingTab = true;
		}
		else if (!playerKeyboard["TAB"]) {
			holdingTab = false;
		}

		// Update player
		player.rot += player.rotSpeed;

		glm::vec2 acceleration;
		acceleration.x = (player.forwardAccel * -sin(player.rot));
		acceleration.y = (player.forwardAccel * cos(player.rot));
		
		player.speed += (acceleration * (float)deltaSecs);

		player.pos += (player.speed * (float)deltaSecs);
		
		shipSprite.setPos(player.pos - (player.size * 0.5f));
		
		shipSprite.setRot(player.rot);

		//camera.setCamPos(player.pos - glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		camera.setCamPos(player.pos);
		
		if (player.camMode == PlayerShip::CameraMode::NORMAL) {
			camera.setCamRot(0);
		}
		else {
			camera.setCamRot(-player.rot);
		}
			

		window.clear();
		camera.update();
		
		// Begin draw
		int currentSectorX = player.pos.x / universe.sectorSize.x;
		int currentSectorY = player.pos.y / universe.sectorSize.y;

		int currentSectorIndex = currentSectorX + (currentSectorY * universe.sectorCountX);
		
		/*
		if (currentSectorIndex >= 0 && currentSectorIndex < universe.sectors.size()) {
			universe.sectors[currentSectorIndex]->drawSector(shader0);
		}
		*/

		for (unsigned int i = 0; i < universe.sectors.size(); i++) {
			universe.sectors[i]->drawSectorBG(shader0);
		}
		for (unsigned int i = 0; i < universe.sectors.size(); i++) {
			universe.sectors[i]->drawSectorPlanets(shader0);
		}
		
		shipSprite.draw(shader0);

		// End draw
		window.swapBuffer();
		
		FR::ResourceManager::unuseShader();
		FR::ResourceManager::unbindTexture();
	}

	FR::ResourceManager::unuseShader();
	FR::ResourceManager::unbindTexture();
	
	return 0;
	
	
}