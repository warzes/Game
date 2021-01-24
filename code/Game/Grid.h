#pragma once

#include "Renderable.h"
#include "AABB.h"

class Grid : public Renderable
{
public:
	Grid() {}
	Grid(float x, float y, float width, float height, int step, const Color& color);

private:
	void buildVertices();
	float mX, mY, mWidth, mHeight;
	int mStep;
	Color mColor;
};