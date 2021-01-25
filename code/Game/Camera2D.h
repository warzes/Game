#pragma once

#include "AABB.h"

class Camera2D
{
public:
	Camera2D() = default;
	Camera2D(float screenWidth, float screenHeight, float scale, float speed);
	void SetPos(float x, float y);
	void SetPos(const glm::vec2& pos);
	glm::vec2 GetPos()  const { return m_pos; }
	glm::mat4 GetMatrix();
	void SetScale(float scale)
	{
		if (m_scale != scale)
		{
			m_scale = scale;
			m_dirty = true;
		}		
	}
	float GetScale() const { return m_scale; }
	float GetX() const { return m_pos.x; }
	float GetY()  const { return m_pos.y; }
	AABB GetAABB();

	void SetScrDim(float screenWidth, float screenHeight)
	{
		if (m_scrDim.x != screenWidth || m_scrDim.y != screenHeight)
		{
			m_scrDim.x = screenWidth;
			m_scrDim.y = screenHeight;
			m_dirty = true;
		}
	}

private:
	void computeMatrix();
	glm::vec2 m_pos;
	glm::vec2 m_scrDim;
	float m_scale = 0.0f, m_speed = 0.0f;
	glm::mat4 m_matrix;
	bool m_dirty = false;
};