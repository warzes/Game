#include "stdafx.h"
#if EXAMPLE_TEST
#include "Ball.h"
#include "TestGame.h"

void Ball::SetPos(const glm::vec2& pos)
{
    m_Pos = pos;
    mSprite.SetPos(pos.x, pos.y);
}

void Ball::Update(float dt)
{
    glm::vec2 pos = GetPos();
    pos += m_Velocity * dt;
    CheckCollisions(pos);
}

bool Ball::CheckCollisions(glm::vec2& newPos)
{
    auto& game = Game::Get();


    bool collided = false;
    const std::vector<Entity*> entities = game.GetEntities();
    for (unsigned i = 0; i < entities.size(); i++)
    {
        if (entities[i] == this || entities[i]->GetType() == PLAYER)
            continue;
        if (GetAABB().Intersects(entities[i]->GetAABB())) {
            collided = true;
            switch (entities[i]->GetType()) {
            case BRICK:
                BrickCollision(newPos, entities[i]);
                break;
            case BALL:
                BallCollision(newPos, (Ball*)entities[i]);
                break;
            }
        }
        SetPos(newPos);
        // if (GetAABB().Intersects(entities[i]->GetAABB())) {
        //     printf("Ball collision not solved with %s\n",
        //         entities[i]->GetType() == BALL ? "ball" : "brick");
        // }
    }

    return collided;
}

void Ball::BrickCollision(glm::vec2& newPos, Entity* brick)
{
    AABB pAABB = GetAABB();
    AABB bAABB = brick->GetAABB();

    glm::vec2 depth(GetWidth(), GetHeight());

    if (pAABB.minX < bAABB.maxX && bAABB.maxX < pAABB.maxX)
        depth.x = -(bAABB.maxX - pAABB.minX);
    else if (pAABB.maxX > bAABB.minX && bAABB.minX > pAABB.minX)
        depth.x = pAABB.maxX - bAABB.minX;
    if (pAABB.minY < bAABB.maxY && bAABB.maxY < pAABB.maxY)
        depth.y = -(bAABB.maxY - pAABB.minY);
    else if (pAABB.maxY > bAABB.minY && bAABB.minY > pAABB.minY)
        depth.y = pAABB.maxY - bAABB.minY;

    if (fabs(depth.x) < fabs(depth.y)) {
        m_Velocity.x *= -1;
        newPos.x -= depth.x;
    }
    else {
        m_Velocity.y *= -1;
        newPos.y -= depth.y;
    }
}

void Ball::BallCollision(glm::vec2& newPos, Ball* other)
{
    float oRadius = other->GetRadius();
    float minDist = mRadius + oRadius;
    const glm::vec2 v2Dist(
        m_Pos.x + mRadius - (other->GetPos().x + oRadius),
        m_Pos.y + mRadius - (other->GetPos().y + oRadius));
    float dist = glm::length(v2Dist);

    if (minDist < dist)
        return;
    if (!dist) // XXX bad position, avoid 0
        return;

    float depth = minDist - dist;
    glm::vec2 v2ColDept = glm::normalize(v2Dist) * depth;
    v2ColDept *= 0.5;
    newPos += v2ColDept;
    other->SetPos(other->GetPos() - v2ColDept);

    float arc = mRadius * mRadius * mRadius;
    float brc = oRadius * oRadius * oRadius;
    glm::vec2 aVNew = m_Velocity * (arc - brc);
    aVNew = aVNew + other->GetVelocity() * (2 * brc);
    aVNew = aVNew / (arc + brc);

    glm::vec2 bVNew = other->GetVelocity() * (brc - arc);
    bVNew = bVNew + m_Velocity * (2 * arc);
    bVNew = bVNew / (arc + brc);

    m_Velocity = aVNew;
    other->SetVelocity(bVNew);
}

#endif