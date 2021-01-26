#pragma once

#if EXAMPLE_TEST

#include "Entity.h"
#include "DrawMultiSprite.h"

class Player : public Entity 
{
public:
    Player(float x, float y, float width, float height, std::shared_ptr<Texture2D> tex);

    void SetSpriteNumFrames(unsigned x, unsigned y) { mSprite.SetNumFrames(x, y); }
    void SetPos(const glm::vec2& pos);

    void Update(float dt) override;
    Renderable* GetRenderable() { return &mSprite; }

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
    DrawMultiSprite mSprite;

    bool CheckCollisions(glm::vec2& newPos);
    void BrickCollision(glm::vec2& newPos, Entity* brick);
    void BallCollision(glm::vec2& newPos, Entity* other);
};

#endif