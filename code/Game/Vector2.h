#pragma once

#include "IntPoint.h"
#include "CoreMath.h"

class Vector2
{
public:
	Vector2() = default;
	Vector2(float nx, float ny) : x(nx), y(ny) {}
	Vector2(const Vector2& p) : x(p.x), y(p.y) {}
	Vector2(const IntPoint& p) : x(static_cast<float>(p.x)), y(static_cast<float>(p.y)) {}

	inline Vector2 operator+(float a) const;
	inline Vector2 operator+(const Vector2& v) const;

	inline Vector2 operator-() const;
	inline Vector2 operator-(float a) const;
	inline Vector2 operator-(const Vector2& v) const;

	inline Vector2 operator*(float scale) const;
	inline Vector2 operator*(const Vector2& v) const;

	inline Vector2 operator/(float scale) const;
	inline Vector2 operator/(const Vector2& v) const;

	inline Vector2 operator+=(const Vector2& v);
	inline Vector2 operator-=(const Vector2& v);
	inline Vector2 operator*=(float scale);
	inline Vector2 operator*=(const Vector2& v);
	inline Vector2 operator/=(float v);
	inline Vector2 operator/=(const Vector2& v);

	inline bool operator==(const Vector2& v) const;
	inline bool operator!=(const Vector2& v) const;
	inline bool operator<(const Vector2& other) const;
	inline bool operator>(const Vector2& other) const;
	inline bool operator<=(const Vector2& other) const;
	inline bool operator>=(const Vector2& other) const;
	
	inline float& operator[](unsigned index);
	inline float operator[](unsigned index) const;

	inline bool Equals(const Vector2& v, float tolerance = SE_SMALL_NUMBER) const;

	inline void Set(float inX, float inY);

	float x = 0.0f;
	float y = 0.0f;
};

inline Vector2 operator*(float scale, const Vector2& v)
{
	return v.operator*(scale);
}

inline Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

inline Vector2 Vector2::operator*(float scale) const
{
	return Vector2(x * scale, y * scale);
}

inline Vector2 Vector2::operator/(float scale) const
{
	const float invScale = 1.f / scale;
	return Vector2(x * invScale, y * invScale);
}

inline Vector2 Vector2::operator+(float a) const
{
	return Vector2(x + a, y + a);
}

inline Vector2 Vector2::operator-(float a) const
{
	return Vector2(x - a, y - a);
}

inline Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

inline Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(x / v.x, y / v.y);
}

inline bool Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}

inline bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

inline bool Vector2::operator<(const Vector2& other) const
{
	return x < other.x&& y < other.y;
}

inline bool Vector2::operator>(const Vector2& other) const
{
	return x > other.x && y > other.y;
}

inline bool Vector2::operator<=(const Vector2& other) const
{
	return x <= other.x && y <= other.y;
}

inline bool Vector2::operator>=(const Vector2& other) const
{
	return x >= other.x && y >= other.y;
}

inline Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

inline Vector2 Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline Vector2 Vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

inline Vector2 Vector2::operator/=(float v)
{
	const float invF = 1.f / v;
	x *= invF;
	y *= invF;
	return *this;
}

inline Vector2 Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline Vector2 Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

inline float& Vector2::operator[](unsigned index)
{
	return ((index == 0) ? x : y);
}

inline float Vector2::operator[](unsigned index) const
{
	return ((index == 0) ? x : y);
}

inline bool Vector2::Equals(const Vector2& v, float tolerance) const
{
	return fabsf(x - v.x) <= tolerance && fabsf(y - v.y) <= tolerance;
}

inline void Vector2::Set(float inX, float inY)
{
	x = inX;
	y = inY;
}