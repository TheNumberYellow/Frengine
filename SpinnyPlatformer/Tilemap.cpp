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

void Tilemap::create(std::vector<FR::Texture2D*> tileTextures, std::vector<int> tiles, int tileCountX, int tileCountY) {
	_tileCountX = tileCountX;
	_tileCountY = tileCountY;

	_tileNums = tiles;

	for (int i = 0; i < tiles.size(); ++i) {
		// Negative value denotes no tile
		if (tiles[i] < 0) {
			continue;
		}

		int tilePosX = i % tileCountX;
		int tilePosY = i / tileCountX;

		float tileWidth = 80;
		float tileHeight = 80;

		FR::Sprite* newSprite = new FR::Sprite(glm::vec2(tilePosX * tileWidth, tilePosY * tileHeight), glm::vec2(tileWidth, tileHeight), 0, tileTextures[tiles[i]]);

		_tiles.push_back(newSprite);
	}
}