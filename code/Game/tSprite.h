#pragma once

#if EXAMPLE_TEST

#include "FilledRectangle.h"

class Sprite : public FilledRectangle
{
public:
    Sprite(float x, float y, float width, float height, const Color& color, unsigned texId);
    Sprite(float width, float height, unsigned texId);
};

#endif