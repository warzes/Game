#pragma once

#if EXAMPLE_TEST

#include "DrawRectangle.h"

class Sprite : public DrawRectangle
{
public:
    Sprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex);
    Sprite(float width, float height, std::shared_ptr<Texture2D> tex);
};

#endif