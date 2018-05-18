#pragma once

#include "Tilemap.h"

// Returns resulting position



struct Player {
	glm::vec2 playerPos = glm::vec2(120, 120);
	FR::Sprite playerSprite;

	glm::vec2 playerSpeed = glm::vec2(0, 0);
	bool jumping = true;
	float jumpAccel = 100.0;

	// PLAYER POSITION AND TILE SIZE ARE IN **PIXEL COORDINATES** FOR NOW
	glm::vec2 CollisionSolver(const Tilemap &tm, double delta);
	
	void update(double delta, Tilemap tm);
	void draw(FR::ShaderProgram* shader);
	void jump(double delta);

	static bool get2dLineIntersection(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2* intersection);

};