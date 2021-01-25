#include "stdafx.h"
#include "Texture2D.h"
#include "OGLFunc.h"
//-----------------------------------------------------------------------------
Texture2D::Texture2D()
{
}
//-----------------------------------------------------------------------------
Texture2D::~Texture2D()
{
	//glDeleteTextures(1, &ID);
	//ID = 0;
}
//-----------------------------------------------------------------------------
void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	Width = width;
	Height = height;
	// create Texture
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
	// set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
	glGenerateMipmap(GL_TEXTURE_2D);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
//-----------------------------------------------------------------------------
void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
//-----------------------------------------------------------------------------