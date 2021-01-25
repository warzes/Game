#include "stdafx.h"
#if EXAMPLE_TEST
#include "Sprite.h"

Sprite::Sprite(float x, float y, float width, float height, const Color& color, unsigned tex)
	: FilledRectangle(x, y, width, height, color)
{
	TextureId = tex;
}

Sprite::Sprite(float width, float height, unsigned tex)
	: FilledRectangle(0, 0, width, height, Color(255, 255, 255, 255))
{
	TextureId = tex;
}
#endif