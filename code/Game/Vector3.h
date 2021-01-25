#pragma once

class Vector3
{
public:
	Vector3() = default;
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};