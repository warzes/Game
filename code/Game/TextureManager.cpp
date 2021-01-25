#include "stdafx.h"
#include "TextureManager.h"
#include "OGLFunc.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION
//-----------------------------------------------------------------------------
std::map<std::string, Texture2D> TextureManager::Textures;
//-----------------------------------------------------------------------------
Texture2D TextureManager::LoadTexture(const char* file, bool alpha, const std::string& name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}
//-----------------------------------------------------------------------------
Texture2D TextureManager::GetTexture(const std::string& name)
{
	return Textures[name];
}
//-----------------------------------------------------------------------------
void TextureManager::Clear()
{
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
	Textures.clear();
}
//-----------------------------------------------------------------------------
Texture2D TextureManager::loadTextureFromFile(const char* file, bool alpha)
{
	int desired_channels = 0;
	// create texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
		desired_channels = STBI_rgb_alpha;
	}
	else
	{
		texture.Internal_Format = GL_RGB;
		texture.Image_Format = GL_RGB;
		desired_channels = STBI_rgb;
	}
	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, desired_channels);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}
//-----------------------------------------------------------------------------