#include "stdafx.h"
#if EXAMPLE_TEST
#include "tRectangle.h"
//-----------------------------------------------------------------------------
Rectangle2::Rectangle2(float x, float y, float width, float height, const Color& color)
	: m_X(x)
	, m_Y(y)
	, m_Width(width)
	, m_Height(height)
	, m_Color(color)
	, m_UV(0, 0, 1, 1)
{
	vertices.resize(4);
	indexes = { LB, LT, LT, RT, RT, RB, RB, LB };
	drawType = DrawType::Lines;
	buildVertices();
}
//-----------------------------------------------------------------------------
void Rectangle2::SetPos(float x, float y, float z)
{
	if (m_X == x && m_Y == y)
		return;
	m_X = x;
	m_Y = y;
	m_z = z;
	buildVertices();
}
//-----------------------------------------------------------------------------
void Rectangle2::SetPos(const glm::vec2& pos, float z)
{
	SetPos(pos.x, pos.y, z);
}
//-----------------------------------------------------------------------------
void Rectangle2::SetColor(const Color& color)
{
	m_Color = color;
	buildVertices();
}
//-----------------------------------------------------------------------------
void Rectangle2::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_Color = Color(r, g, b, a);
	buildVertices();
}
//-----------------------------------------------------------------------------
void Rectangle2::SetUV(AABB uv)
{
	m_UV = uv;
	buildVertices();
}
//-----------------------------------------------------------------------------
void Rectangle2::buildVertices()
{
	vertices[LB].SetPos(m_X, m_Y, m_z);
	vertices[LT].SetPos(m_X, m_Y + m_Height, m_z);
	vertices[RT].SetPos(m_X + m_Width, m_Y + m_Height, m_z);
	vertices[RB].SetPos(m_X + m_Width, m_Y, m_z);

	for (size_t i = 0; i < vertices.size(); i++)
		vertices[i].SetColor(m_Color);

	vertices[LB].SetUV(m_UV.minX, m_UV.minY);
	vertices[LT].SetUV(m_UV.minX, m_UV.maxY);
	vertices[RT].SetUV(m_UV.maxX, m_UV.maxY);
	vertices[RB].SetUV(m_UV.maxX, m_UV.minY);
}
//-----------------------------------------------------------------------------
#endif