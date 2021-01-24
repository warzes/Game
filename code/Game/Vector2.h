#pragma once

class Vector2
{
public:
	Vector2() = default;
	Vector2(float nx, float ny) : x(nx), y(ny) {}

	float x = 0.0f;
	float y = 0.0f;
};