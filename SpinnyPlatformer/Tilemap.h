#pragma once

#include <Frengine\Sprite.h>
#include <Frengine\ResourceManager.h>

#include <vector>

class Tilemap {
public:
	Tilemap();
	~Tilemap();
	
	void draw(FR::ShaderProgram* shader);
	void create(std::vector<FR::Texture2D*> tileTextures, std::vector<int> tiles, int tileCountX, int tileCountY, glm::vec2 tileSize);

	glm::vec2 _tileSize;
	
	std::vector<int> _tileNums;
	int _tileCountX, _tileCountY;

private:
	std::vector<FR::Sprite*> _tiles;


};

