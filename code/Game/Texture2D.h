#pragma once

class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind() const;

	unsigned int ID;
	// texture image dimensions
	unsigned int Width = 0, Height = 0;    // width and height of loaded image in pixels
	// texture Format
	unsigned int Internal_Format = GL_RGBA;// format of texture object
	unsigned int Image_Format = GL_RGBA;   // format of loaded image
	// texture configuration
	unsigned int Wrap_S = GL_REPEAT;       // wrapping mode on S axis
	unsigned int Wrap_T = GL_REPEAT;       // wrapping mode on T axis
	unsigned int Filter_Min = GL_LINEAR_MIPMAP_NEAREST;// filtering mode if texture pixels < screen pixels
	unsigned int Filter_Max = GL_NEAREST;  // filtering mode if texture pixels > screen pixels
};