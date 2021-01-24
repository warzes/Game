#pragma once

#include "Texture2D.h"

class TextureManager
{
public:
	// loads (and generates) a texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, const std::string& name);
	// retrieves a stored texture
	static Texture2D GetTexture(const std::string& name);

	static void Clear();

	static std::map<std::string, Texture2D> Textures;

private:
	TextureManager() = delete;

	// loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};