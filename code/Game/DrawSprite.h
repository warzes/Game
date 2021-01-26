#pragma once

#include "DrawRectangle.h"

class DrawSprite : public DrawRectangle
{
public:
    DrawSprite();
    DrawSprite(float x, float y, float width, float height, const Color& color, std::shared_ptr<Texture2D> tex);
    DrawSprite(float width, float height, std::shared_ptr<Texture2D> tex);
};