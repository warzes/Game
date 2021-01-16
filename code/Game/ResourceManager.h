#pragma once

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2D> Textures;
	// loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	// retrieves a stored sader
	static Shader GetShader(std::string name);
	// loads (and generates) a texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	// retrieves a stored texture
	static Texture2D GetTexture(std::string name);
	// properly de-allocates all loaded resources
	static void Clear();
private:
	ResourceManager() = delete;
	// loads and generates a shader from file
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	// loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};