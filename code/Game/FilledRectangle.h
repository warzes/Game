#pragma once
#if EXAMPLE_TEST
#include "Rectangle.h"

class FilledRectangle : public Rectangle2
{
public:
	FilledRectangle(float x, float y, float width, float height, const Color& color);
};
#endif