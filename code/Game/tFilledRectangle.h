#pragma once
#if EXAMPLE_TEST
#include"DrawRectangle.h"

class FilledRectangle : public DrawRectangle
{
public:
	FilledRectangle(float x, float y, float width, float height, const Color& color);
};
#endif