#pragma once
#if EXAMPLE_TEST
#include "Sprite.h"

class MultiSprite : public Sprite 
{
public:
	MultiSprite(float width, float height, unsigned tex);
	MultiSprite(float x, float y, float width, float height, const Color& color, unsigned tex);
	void SetNumFrames(int numX, int numY);
	void SetFrame(int x, int y);

private:
	int mNumX, mNumY;
};
#endif