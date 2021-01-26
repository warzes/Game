#pragma once

#if EXAMPLE_TEST

#include "tFilledRectangle.h"

class Sprite : public FilledRectangle
{
public:
    Sprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex);
    Sprite(float width, float height, std::shared_ptr<Texture2D> tex);
};

#endif