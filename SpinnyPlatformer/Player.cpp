#include "Player.h"

// PLAYER POSITION AND TILE SIZE ARE IN **PIXEL COORDINATES** FOR NOW

glm::vec2 Player::CollisionSolver(const Tilemap & tm, double delta) {
	glm::vec2 resultVec;

	glm::vec2 newPos = this->playerPos + (this->playerSpeed * (float)delta);

	int tilePosX, tilePosY;

	tilePosX = (newPos.x / tm._tileSize.x);
	tilePosY = (newPos.y / tm._tileSize.y);

	if (tm._tileNums[tilePosX + (tilePosY * tm._tileCountX)] != -1) {
		resultVec = this->playerPos;
		this->playerSpeed = glm::vec2(0, 0);
	}
	else {
		resultVec = newPos;
	}
	return resultVec;
}

void Player::update(double delta, Tilemap tm) {
	//playerPos += (float)delta * playerSpeed;
	playerPos = CollisionSolver(tm, delta);

	playerSprite.setPos(playerPos - (playerSprite.getScale() * 0.5f));
}

void Player::draw(FR::ShaderProgram * shader) {
	playerSprite.draw(shader);
}

void Player::jump(double delta) {
	playerSpeed.y -= jumpAccel * delta;
	jumping = true;
}

bool Player::get2dLineIntersection(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 * intersection)
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
