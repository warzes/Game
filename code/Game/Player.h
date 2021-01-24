#pragma once

#include "Entity.h"
#include "MultiSprite.h"

class Player : public Entity 
{
public:
    Player(float x, float y, float width, float height, unsigned texId);

    void SetSpriteNumFrames(unsigned x, unsigned y) { mSprite.SetNumFrames(x, y); }
    void SetPos(const glm::vec2& pos);

    void Update(unsigned ticks) override;
    Renderable* GetRenderable() { return &mSprite; }

private:
    float mAnimSpeed;
    float mSpeed;
    MultiSprite mSprite;

    bool CheckCollisions(unsigned ticks, glm::vec2& newPos);
    void BrickCollision(glm::vec2& newPos, Entity* brick);
    void BallCollision(unsigned ticks, glm::vec2& newPos, Entity* other);
};