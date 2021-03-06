#pragma once
#include <GL\glew.h>

#include <map>

#include "GLTexture.h"
#include "ShaderProgram.h"

namespace FR {
	class ResourceManager {
	public:
		// Retrieve stored texture
		static Texture2D* getTexture(std::string textureName);
		// Load texture from file
		static Texture2D* loadTexture(std::string filePath, std::string name);

		// Retrieve stored shader
		static ShaderProgram* getShader(std::string shaderName);
		// Load, compile and link shader program from shader files
		static ShaderProgram* loadShaderProgram(std::string vertFilePath, std::string fragFilePath, std::string name);
		static ShaderProgram* getDefaultShader();

		static void unbindTexture();
		static void unuseShader();
	private:
		static std::map<std::string, Texture2D*> _textures;
		static std::map<std::string, ShaderProgram*> _shaders;
		static ShaderProgram* defaultShader;

		static bool defaultShaderLoaded;
		
		static ShaderProgram* loadDefaultShader();
	};
}
