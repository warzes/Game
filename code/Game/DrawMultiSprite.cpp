#include "stdafx.h"
#include "DrawMultiSprite.h"
//-----------------------------------------------------------------------------
DrawMultiSprite::DrawMultiSprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex)
	: DrawSprite(x, y, width, height, color, tex)
	, m_numFrameX(1)
	, m_numFrameY(1)
{
}
//-----------------------------------------------------------------------------
DrawMultiSprite::DrawMultiSprite(float width, float height, std::shared_ptr<Texture2D> tex)
	: DrawSprite(width, height, tex)
	, m_numFrameX(1)
	, m_numFrameY(1)
{
}
//-----------------------------------------------------------------------------
void DrawMultiSprite::SetNumFrames(int numX, int numY)
{
	m_numFrameX = numX;
	m_numFrameY = numY;
	SetFrame(0, 0);
}
//-----------------------------------------------------------------------------
void DrawMultiSprite::SetFrame(int x, int y)
{
	y = m_numFrameY - y - 1; // reverse, to count from top left
	float fx = 1.0f / m_numFrameX;
	float fy = 1.0f / m_numFrameY;

	AABB uv(x * fx, y * fy, (x + 1) * fx, (y + 1) * fy);
	SetUV(uv);
}
//-----------------------------------------------------------------------------