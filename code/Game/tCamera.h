#pragma once

#if EXAMPLE_TEST

#include "AABB.h"

class tCamera
{
public:
	tCamera() = default;
	tCamera(float screenWidth, float screenHeight, float scale, float speed);
	void SetPos(float x, float y);
	void SetPos(const glm::vec2& pos);
	glm::vec2 GetPos() { return m_Pos; }
	glm::mat4 GetMatrix();
	void SetMatrix(unsigned int programId, const std::string& name);
	void SetScale(float scale)
	{
		m_Scale = scale;
		m_Dirty = true;
	}
	float GetScale() { return m_Scale; }
	float GetX() { return m_Pos.x; }
	float GetY() { return m_Pos.y; }
	AABB GetAABB();

private:
	void computeMatrix();
	glm::vec2 m_Pos;
	glm::vec2 m_ScrDim;
	float m_Scale = 0.0f, m_Speed = 0.0f;
	glm::mat4 m_Matrix;
	bool m_Dirty = false;
};

#endif