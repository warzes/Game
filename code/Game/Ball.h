#pragma once

#if EXAMPLE_TEST

#include "tEntity.h"
#include "DrawSprite.h"

enum EntityType {
    NO_ENTITY,
    BALL,
    BRICK,
    FLOOR,
    PLAYER
};

class Ball : public Entity 
{
public:
    Ball(float x, float y, float radius, std::shared_ptr<Texture2D> tex)
        : Entity(x, y, 2 * radius, 2 * radius)
        , mRadius(radius)
        , mSprite(2 * radius, 2 * radius, tex)
    {
        m_Type = BALL;
        mSprite.SetPos(x, y);
    }

    float GetRadius() { return mRadius; }
    void Update(float dt) override;
    bool CheckCollisions(glm::vec2& newPos);
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
    DrawSprite mSprite;
};

#endif