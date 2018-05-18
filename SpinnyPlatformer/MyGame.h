#pragma once
#include <Frengine\Game.h>

#include <iostream>

class MyGame : public FR::Game
{
public:
	MyGame();
	~MyGame();
private:

	// Implement pure virtual function SetUp and Update
	virtual void SetUp();
	virtual void Update(double delta);

	// Override virtual functions KeyDown and KeyUp
	virtual void KeyDown(SDL_Keycode key);
	virtual void KeyUp(SDL_Keycode key);

	virtual void MouseClicked(int x, int y);

	bool get2dLineIntersection(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2* intersection);

	std::vector<glm::vec2> points;
};

