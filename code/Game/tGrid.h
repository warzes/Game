#pragma once
#if EXAMPLE_TEST
#include "tRenderable.h"
#include "AABB.h"

class Grid : public tRenderable
{
public:
	Grid() {}
	Grid(float x, float y, float width, float height, int step, const Color& color);

private:
	void buildVertices();
	float mX, mY, mWidth, mHeight;
	float m_z = 0.0f; // TODO: слой сетки
	int mStep;
	Color mColor;
};
#endif