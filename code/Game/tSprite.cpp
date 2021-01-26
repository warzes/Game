#include "stdafx.h"
#if EXAMPLE_TEST
#include "tSprite.h"

Sprite::Sprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex)
	: DrawRectangle(x, y, width, height, color, TypeDrawRectangle::Filled)
{
	texture = tex;
}

Sprite::Sprite(float width, float height, std::shared_ptr<Texture2D> tex)
	: DrawRectangle(0, 0, width, height, Color(255, 255, 255, 255), TypeDrawRectangle::Filled)
{
	texture = tex;
}
#endif