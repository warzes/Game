#pragma once

#include "AABB.h"

class Entity
{
public:
	Entity(float x, float y, float width, float height)
		: m_type(0)
		, m_pos(x, y)
		, m_dim(width, height)
		, m_velocity(0)
	{
	}
	virtual ~Entity() = default;

	virtual void SetPos(const glm::vec2& pos) { m_pos = pos; }
	const glm::vec2& GetPos() const { return m_pos; }

	const glm::vec2& GetDim() const { return m_dim; }
	float GetWidth() const { return m_dim.x; }
	float GetHeight() const { return m_dim.y; }

	AABB GetAABB() const
	{
		return AABB(m_pos.x, m_pos.y, m_pos.x + m_dim.x, m_pos.y + m_dim.y);
	}

	void SetVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
	const glm::vec2& GetVelocity() const { return m_velocity; }

	int GetType() const { return m_type; }

	virtual void Update(float /*dt*/){}

protected:
	int m_type; // this will be game specific.
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	glm::vec2 m_velocity;
};