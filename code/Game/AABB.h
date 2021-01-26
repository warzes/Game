#pragma once

#include "Vector2.h"

class AABB
{
public:
	AABB(float x1, float y1, float x2, float y2);

	bool Intersects(const AABB& other);
	bool FitsIn(const AABB& other) const;

	/* Gets the distance between center of rectangles. */
	glm::vec2 GetDistance(const AABB& other) const;
	float GetWidth() const { return maxX - minX; }
	float GetHeight() const { return maxY - minY; }
	glm::vec2 GetMin() const { return glm::vec2(minX, minY); }
	glm::vec2 GetMax() const { return glm::vec2(maxX, maxY); }
	glm::vec2 GetCenter() const { return glm::vec2(minX + (maxX - minX) / 2, minY + (maxY - minY) / 2); }
	glm::vec2 GetIntersectionDepth(const AABB& other) const;

	float minX = 0.0f;
	float minY = 0.0f;
	float maxX = 0.0f;
	float maxY = 0.0f;
};