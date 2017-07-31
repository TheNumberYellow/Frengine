#include "ResourceManager.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace FR;

//  Instantiate static variables
std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, ShaderProgram*> ResourceManager::_shaders;


Texture2D* ResourceManager::getTexture(std::string textureName) {
	std::map<std::string, Texture2D*>::iterator it = _textures.find(textureName);

	if (it == _textures.end()) {
		printf("ResourceManager Error: Could not find texture %s in texture cache.\n", textureName);
		return nullptr;
	}
	return it->second;
}

void ResourceManager::loadTexture(std::string filePath, std::string name) {
	// Load texture from file path
	int width, height, channels;
	unsigned char* imgData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

	if (imgData == nullptr) {
		printf("ResourceManager Error: Invalid image file. (File likely missing or corrupted) \n");
		return;
	}

	// TEMP
	//printf("Channels in file loaded: %i.\n", channels);

	// Generate texture
	Texture2D* newTexture = new Texture2D;

	// Set appropriate image format
	switch (channels) {
	case 3:
		newTexture->setFormat(GL_RGB);
		break;
	case 4:
		newTexture->setFormat(GL_RGBA);
		break;
	}

	newTexture->generate(imgData, width, height);
	
	// Add texture to map
	_textures[name] = newTexture;

	// Free texture data
	stbi_image_free(imgData);

	return;
}

ShaderProgram* ResourceManager::getShader(std::string shaderName) {
	std::map<std::string, ShaderProgram*>::iterator it = _shaders.find("shaderName");

	if (it == _shaders.end()) {
		printf("ResourceManager Error: Could not find shaderprogram %s in shader cache.\n", shaderName);
		return nullptr;
	}

	return it->second;
}

void ResourceManager::loadShaderProgram(std::string vertFilePath, std::string fragFilePath, std::string name) {
}

void ResourceManager::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ResourceManager::unuseShader() {
	glUseProgram(0);
}