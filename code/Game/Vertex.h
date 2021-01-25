#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

class BaseVertexColor
{
public:
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { color.r = r, color.g = g, color.b = b, color.a = a; }
	void SetColor(const Color& ncolor) { color = ncolor; }

	Color color;
};

class BaseVertexUV
{
public:
	void SetUV(float x, float y) { uv.x = x, uv.y = y; }
	void SetUV(const Vector2& nuv) { uv = nuv; }
	Vector2 uv;
};

class BaseVertex3Pos
{
public:
	void SetPos(float x, float y, float z) { pos.x = x, pos.y = y; pos.z = z; }
	void SetPos(const Vector3& npos) { pos = npos; }

	Vector3 pos;
};


class Vertex3PCT : public BaseVertex3Pos, public BaseVertexColor, public BaseVertexUV
{
public:

};