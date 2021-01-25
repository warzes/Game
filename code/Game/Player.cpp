#include "stdafx.h"
#include "Player.h"
#include "Ball.h"
#include "Keyboard.h"
#include "TestGame.h"

Player::Player(float x, float y, float width, float height, unsigned texId)
    : Entity(x, y, width, height)
    , mAnimSpeed(0.01f * 2000.0f)
    , mSpeed(0.3f)
    , mSprite(width, height, texId)
{
    m_Type = PLAYER;
    mSprite.SetPos(m_Pos);
}

void Player::SetPos(const glm::vec2& pos)
{
    m_Pos = pos;
    mSprite.SetPos(pos);
}

void Player::Update(float dt)
{
    glm::vec2 velocity = glm::vec2(0);


    if (Keyboard::Get().KeyDown(Keyboard::KEY_W))
        velocity.y = 1;
    else if (Keyboard::Get().KeyDown(Keyboard::KEY_S))
        velocity.y = -1;
    if (Keyboard::Get().KeyDown(Keyboard::KEY_A))
        velocity.x = -1;
    else if (Keyboard::Get().KeyDown(Keyboard::KEY_D))
        velocity.x = 1;

    velocity *= mSpeed;

    glm::vec2 pos = GetPos();
    pos += velocity * dt * 2000.0f;
    CheckCollisions(pos);

    // this is too texture dependent    
    static float frameX = 0;

    pState = P_WALK;
    if (velocity.x < 0)
        pFace = F_LEFT;
    else if (velocity.x > 0)
        pFace = F_RIGHT;
    else if (velocity.y < 0)
        pFace = F_DOWN;
    else if (velocity.y > 0)
        pFace = F_UP;
    else
        pState = P_STOP;

    frameX = pState * ((frameX + mAnimSpeed * dt));
    if (frameX > 5.0f)
        frameX = 0;

    mSprite.SetFrame(floor(frameX) + 1, pFace);
    // update velocity if is not 0 (so we keep track of previous one)
    if (velocity.x || velocity.y)
        m_Velocity = velocity;
}

bool Player::CheckCollisions(glm::vec2& newPos)
{
    bool collided = false;

    auto& game = Game::Get();

    const std::vector<Entity*> entities = game.GetEntities();
    for (unsigned i = 0; i < entities.size(); i++)
    {
        if (entities[i] == this)
            continue;
        if (GetAABB().Intersects(entities[i]->GetAABB())) {
            collided = true;
            switch (entities[i]->GetType()) {
            case BRICK:
                BrickCollision(newPos, entities[i]);
                break;
            case BALL:
                BallCollision(newPos, entities[i]);
                break;
            }
        }
        SetPos(newPos);
        if (GetAABB().Intersects(entities[i]->GetAABB())) {
            printf("Player collision not solved with %s\n",
                entities[i]->GetType() == BALL ? "ball" : "brick");
        }
    }

    return collided;
}

void Player::BrickCollision(glm::vec2& newPos, Entity* brick)
{
    AABB pAABB = GetAABB();
    AABB bAABB = brick->GetAABB();

    glm::vec2 depth = pAABB.GetIntersectionDepth(bAABB);

    // TODO - compute the other axis based on velocity vector and do diff also
    // for a more accurate point.
    if (fabs(depth.x) < fabs(depth.y))
        newPos.x -= depth.x;
    else
        newPos.y -= depth.y;
}

void Player::BallCollision(glm::vec2& newPos, Entity* ball)
{
    glm::vec2 depth = GetAABB().GetIntersectionDepth(ball->GetAABB());

    glm::vec2 ballNewPos = ball->GetPos();

    if (fabs(depth.x) < fabs(depth.y)) {
        ballNewPos.x += depth.x;
    }
    else {
        ballNewPos.y += depth.y;
    }
    // check if pushed ball collides with something else
    ((Ball*)ball)->CheckCollisions(ballNewPos);

    if (GetAABB().Intersects(ball->GetAABB())) {
        // step back player
        depth = GetAABB().GetIntersectionDepth(ball->GetAABB());
        if (fabs(depth.x) < fabs(depth.y)) {
            newPos.x -= depth.x;
        }
        else {
            newPos.y -= depth.y;
        }
    }
}