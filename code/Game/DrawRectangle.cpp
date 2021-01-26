#include "stdafx.h"
#include "DrawRectangle.h"

//-----------------------------------------------------------------------------
DrawRectangle::DrawRectangle(float x, float y, float width, float height, const Color& color, TypeDrawRectangle type)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
	, m_color(color)
	, m_type(type)
{
	vertices.resize(4);
	buildTypesAndIndexes();
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetPos(float x, float y, float z)
{
	if (m_x == x && m_y == y && m_z == z)
		return;
	m_x = x;
	m_y = y;
	m_z = z;
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetPos(const Vector2& pos, float z)
{
	SetPos(pos.x, pos.y, z);
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetColor(const Color& color)
{
	m_color = color;
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color = Color(r, g, b, a);
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetUV(AABB uv)
{
	m_uv = uv;
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::SetTypeForm(TypeDrawRectangle type)
{
	m_type = type;
	buildTypesAndIndexes();
	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawRectangle::buildVertices()
{
	vertices[LB].SetPos(m_x, m_y, m_z);
	vertices[LT].SetPos(m_x, m_y + m_height, m_z);
	vertices[RT].SetPos(m_x + m_width, m_y + m_height, m_z);
	vertices[RB].SetPos(m_x + m_width, m_y, m_z);

	for (size_t i = 0; i < vertices.size(); i++)
		vertices[i].SetColor(m_color);

	vertices[LB].SetUV(m_uv.minX, m_uv.minY);
	vertices[LT].SetUV(m_uv.minX, m_uv.maxY);
	vertices[RT].SetUV(m_uv.maxX, m_uv.maxY);
	vertices[RB].SetUV(m_uv.maxX, m_uv.minY);
}
//-----------------------------------------------------------------------------
void DrawRectangle::buildTypesAndIndexes()
{
	indexes.clear();
	if (m_type == TypeDrawRectangle::Points)
	{
		indexes = { LB, LT, RT, RB };
		drawType = DrawType::Points;
	}
	else if (m_type == TypeDrawRectangle::Lines)
	{
		indexes = { LB, LT, LT, RT, RT, RB, RB, LB };
		drawType = DrawType::Lines;
	}
	else if (m_type == TypeDrawRectangle::Filled)
	{
		indexes = { LB, LT, RT, RT, RB, LB };
		drawType = DrawType::Triangles;
	}
}
//-----------------------------------------------------------------------------