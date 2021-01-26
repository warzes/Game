#include "stdafx.h"
#include "DrawSprite.h"
//-----------------------------------------------------------------------------
DrawSprite::DrawSprite()
	: DrawRectangle(0, 0, 0, 0, Color(255, 255, 255, 255), TypeDrawRectangle::Filled)
{
}
//-----------------------------------------------------------------------------
DrawSprite::DrawSprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex)
	: DrawRectangle(x, y, width, height, color, TypeDrawRectangle::Filled)
{
	texture = tex;
}
//-----------------------------------------------------------------------------
DrawSprite::DrawSprite(float width, float height, std::shared_ptr<Texture2D> tex)
	: DrawRectangle(0, 0, width, height, Color(255, 255, 255, 255), TypeDrawRectangle::Filled)
{
	texture = tex;
}
//-----------------------------------------------------------------------------