#pragma once
#if EXAMPLE_TEST
#include "tSprite.h"

class MultiSprite : public Sprite 
{
public:
	MultiSprite(float width, float height, std::shared_ptr<Texture2D> tex);
	MultiSprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex);
	void SetNumFrames(int numX, int numY);
	void SetFrame(int x, int y);

private:
	int mNumX, mNumY;
};
#endif