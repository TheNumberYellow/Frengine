#include "Tilemap.h"

#include <iostream>


Tilemap::Tilemap() {
}


Tilemap::~Tilemap() {
}

void Tilemap::draw(FR::ShaderProgram* shader) {
	for (int i = 0; i < _tiles.size(); ++i) {
		_tiles[i]->draw(shader);
	}
}

void Tilemap::create(std::vector<FR::Texture2D*> tileTextures, std::vector<int> tiles, int tileCountX, int tileCountY, glm::vec2 tileSize) {
	_tileCountX = tileCountX;
	_tileCountY = tileCountY;

	_tileNums = tiles;
	_tileSize = tileSize;

	for (int i = 0; i < tiles.size(); ++i) {
		// Negative value denotes no tile
		if (tiles[i] < 0) {
			continue;
		}

		int tilePosX = tileCountX - (i % tileCountX) - 1;
		int tilePosY = tileCountY - (i / tileCountX) - 1;
		//int tilePosX = (i % tileCountX);
		//int tilePosY = (i / tileCountX);

		
		FR::Sprite* newSprite = new FR::Sprite(glm::vec2(tilePosX * tileSize.x, tilePosY * tileSize.y), tileSize, 0, tileTextures[tiles[i]]);

		_tiles.push_back(newSprite);
	}
}