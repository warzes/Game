#include "stdafx.h"
#if EXAMPLE_TEST
#include "tSprite.h"

Sprite::Sprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex)
	: FilledRectangle(x, y, width, height, color)
{
	texture = tex;
}

Sprite::Sprite(float width, float height, std::shared_ptr<Texture2D> tex)
	: FilledRectangle(0, 0, width, height, Color(255, 255, 255, 255))
{
	texture = tex;
}
#endif