#pragma once

#include "DrawSprite.h"

class DrawMultiSprite : public DrawSprite 
{
public:
	DrawMultiSprite(float width, float height, std::shared_ptr<Texture2D> tex);
	DrawMultiSprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex);
	void SetNumFrames(int numX, int numY);
	void SetFrame(int x, int y);

private:
	int m_numFrameX = 0;
	int m_numFrameY = 0;
};