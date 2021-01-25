#pragma once

#if EXAMPLE_TEST

#include "Entity.h"
#include "MultiSprite.h"

class Player : public Entity 
{
public:
    Player(float x, float y, float width, float height, unsigned texId);

    void SetSpriteNumFrames(unsigned x, unsigned y) { mSprite.SetNumFrames(x, y); }
    void SetPos(const glm::vec2& pos);

    void Update(float dt) override;
    tRenderable* GetRenderable() { return &mSprite; }

private:
    enum {
        F_DOWN,
        F_LEFT,
        F_RIGHT,
        F_UP       
    }; 
    enum {
        P_STOP,
        P_WALK
    };

    int pFace = F_DOWN,
        pState = P_STOP;


    float mAnimSpeed;
    float mSpeed;
    MultiSprite mSprite;

    bool CheckCollisions(glm::vec2& newPos);
    void BrickCollision(glm::vec2& newPos, Entity* brick);
    void BallCollision(glm::vec2& newPos, Entity* other);
};

#endif