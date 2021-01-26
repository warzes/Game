#pragma once
#if EXAMPLE_TEST

#include "tRenderable.h"
#include "AABB.h"

class Rectangle2 : public tRenderable
{
public:
	Rectangle2() : m_UV(0, 0, 1, 1) {}
	Rectangle2(float x, float y, float width, float height, const Color& color);
	void SetPos(float x, float y, float z = 0.0f);
	void SetPos(const glm::vec2& pos, float z = 0.0f);
	glm::vec2 GetPos() { return glm::vec2(m_X, m_Y); }
	void SetColor(const Color& color);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetUV(AABB uv);
	float GetX() { return m_X; }
	float GetY() { return m_Y; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	AABB GetAABB() { return AABB(m_X, m_Y, m_X + m_Width, m_Y + m_Height); }

protected:
	void buildVertices();

	enum 
	{
		LB,
		LT,
		RT,
		RB
	};
	float m_X, m_Y, m_Width, m_Height;
	Color m_Color;
	AABB m_UV;
	float m_z;
};
#endif