#pragma once

#include "Entity.h"
#include "Sprite.h"

enum EntityType {
    NO_ENTITY,
    BALL,
    BRICK,
    PLAYER
};

class Ball : public Entity 
{
public:
    Ball(float x, float y, float radius, unsigned texId)
        : Entity(x, y, 2 * radius, 2 * radius)
        , mRadius(radius)
        , mSprite(2 * radius, 2 * radius, texId)
    {
        m_Type = BALL;
        mSprite.SetPos(x, y);
    }

    float GetRadius() { return mRadius; }
    void Update(unsigned ticks) override;
    bool CheckCollisions(unsigned ticks, glm::vec2& newPos);
    Renderable* GetRenderable() { return &mSprite; }
    void SetColor(const Color& color)
    {
        mSprite.SetColor(color);
    }
    void SetPos(const glm::vec2& pos) override;

private:
    void BrickCollision(glm::vec2& newPos, Entity* brick);
    void BallCollision(glm::vec2& newPos, Ball* other);

    float mRadius;
    Sprite mSprite;
};