#pragma once

// TODO: rename?

#include "Renderable.h"
#include "AABB.h"

class Entity
{
public:
	Entity(float x, float y, float width, float height)
		: m_Type(0)
		, m_Pos(x, y)
		, m_Dim(width, height)
		, m_Velocity(0)
	{
	}
	virtual ~Entity() {}

	virtual void SetPos(const glm::vec2& pos) { m_Pos = pos; }
	const glm::vec2& GetPos() const { return m_Pos; }

	const glm::vec2& GetDim() const { return m_Dim; }
	float GetWidth() const { return m_Dim.x; }
	float GetHeight() const { return m_Dim.y; }

	AABB GetAABB() const
	{
		return AABB(m_Pos.x, m_Pos.y, m_Pos.x + m_Dim.x, m_Pos.y + m_Dim.y);
	}

	void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
	const glm::vec2& GetVelocity() { return m_Velocity; }

	int GetType() const { return m_Type; }

	virtual void Update(float dt)
	{
	}

protected:
	int m_Type; // this will be game specific.
	glm::vec2 m_Pos;
	glm::vec2 m_Dim;
	glm::vec2 m_Velocity;
};