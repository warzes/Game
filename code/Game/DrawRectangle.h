#pragma once

#include "Renderable.h"
#include "AABB.h"

// TODO: переименовать TypeDrawRectangle (и метод установки)
enum class TypeDrawRectangle
{
	Points,
	Lines,
	Filled
};

class DrawRectangle : public Renderable
{
public:
	DrawRectangle() = default;
	DrawRectangle(float x, float y, float width, float height, const Color& color, TypeDrawRectangle type);

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
	float GetWidth() const { return m_width; }
	float GetHeight() const { return m_height; }
	Vector2 GetPos() const { return { m_x, m_y }; }
	AABB GetAABB() const { return AABB(m_x, m_y, m_x + m_width, m_y + m_height); }

	void SetTypeForm(TypeDrawRectangle type);
	void SetPos(float x, float y, float z = 0.0f);
	void SetPos(const Vector2& pos, float z = 0.0f);
	void SetColor(const Color& color);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetUV(AABB uv);

protected:
	void buildVertices();
	void buildTypesAndIndexes();

	// перечисление для определения порядка вершин
	enum
	{
		LB,
		LT,
		RT,
		RB
	};
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
	float m_width = 0.0f;
	float m_height = 0.0f;
	Color m_color;
	AABB m_uv = { 0, 0, 1, 1 };	
	TypeDrawRectangle m_type = TypeDrawRectangle::Lines;
};