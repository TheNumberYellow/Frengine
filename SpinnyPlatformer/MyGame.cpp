#include "MyGame.h"



MyGame::MyGame()
{
}


MyGame::~MyGame()
{
}

void MyGame::SetUp()
{
	SetWindowTitle("My Game");
	SetWindowSize(800, 800);

	FR::ResourceManager::loadTexture("Images/player.png", "player");
	FR::ResourceManager::loadTexture("Images/testPicture.png", "background");

	FR::Sprite* playerSprite = new FR::Sprite(glm::vec2(-50, -50), glm::vec2(100, 100), 0.0, FR::ResourceManager::getTexture("player"));
	FR::Sprite* backgroundSprite = new FR::Sprite(glm::vec2(-200, -200), glm::vec2(400, 400), 0.0, FR::ResourceManager::getTexture("background"));

	//AddDrawableElement(backgroundSprite, "background");
	AddDrawableElement(playerSprite, "player");

	for (int i = 0; i < 4; i++) {
		points.push_back(glm::vec2(0, 0));
	}
}

void MyGame::Update(double delta)
{
	FR::Sprite* playerSprite = (FR::Sprite*)GetDrawable("player");
	
	
	glm::vec2 movement;
	
	float speed = 400.0;

	if (IsKeyPressed(FR::K_UP)) { movement.y += speed; }
	if (IsKeyPressed(FR::K_DOWN)) { movement.y -= speed; }
	if (IsKeyPressed(FR::K_LEFT)) { movement.x -= speed; }
	if (IsKeyPressed(FR::K_RIGHT)) { movement.x += speed; }

	movement *= delta;

	playerSprite->move(movement);
	
}

void MyGame::KeyDown(SDL_Keycode key)
{
}

void MyGame::KeyUp(SDL_Keycode key)
{

}

void MyGame::MouseClicked(int x, int y)
{
	static int numClicked = 0;

	FR::Sprite* newSprite = new FR::Sprite(glm::vec2(x - 400, (800 - y) - 400), glm::vec2(20, 20), 0.0, FR::ResourceManager::getTexture("player"));

	std::string newDotString = "dot" + std::to_string(numClicked);

	AddDrawableElement(newSprite, newDotString);
	points[numClicked] = glm::vec2(x - 400, (800 - y) - 400);

	numClicked++;

	if (numClicked == 4) {
		numClicked = 0;
		glm::vec2 intersect;

		if (get2dLineIntersection(points[0], points[1], points[2], points[3], &intersect)) {
			FR::Sprite* intersectPoint = new FR::Sprite(intersect, glm::vec2(20, 20), 0.0, FR::ResourceManager::getTexture("player"));
			AddDrawableElement(intersectPoint, "Intersection");
			std::cout << "Intersection Occurred" << std::endl;
			std::cout << intersect.x << " " << intersect.y << std::endl;
		}
	}
}

// Solve for intersection between line intersect (p0 -> p1) and (p2 -> p3)
bool MyGame::get2dLineIntersection(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2* intersection)
{
	glm::vec2 s1, s2;
	s1.x = p1.x - p0.x;	
	s1.y = p1.y - p0.y;
	s2.x = p3.x - p2.x;
	s2.y = p3.y - p2.y;

	float s, t;

	s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
	t = (s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		// Collision detected
		if (intersection != NULL) {
			intersection->x = p0.x + (t* s1.x);
			intersection->y = p0.y + (t * s1.y);

		}
		
		return true;
	}
	return false; // No collision
	
}
