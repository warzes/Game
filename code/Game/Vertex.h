#pragma once

#include "Vector2.h"
#include "Color.h"

// 2D Vertex (pos, color, texture)
class Vertex2PCT
{
public:
	void SetPos(float x, float y) { pos.x = x, pos.y = y; }
	void SetPos(const Vector2& npos) { pos = npos; }
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { color.r = r, color.g = g, color.b = b, color.a = a; }
	void SetColor(const Color& ncolor) { color = ncolor; }
	void SetUV(float x, float y) { uv.x = x, uv.y = y; }
	void SetUV(const Vector2& nuv) { uv = uv; }

	Vector2 pos;
	Color color;
	Vector2 uv;
};