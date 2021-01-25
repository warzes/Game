#pragma once

struct IntPoint
{
public:
	IntPoint() = default;
	IntPoint(int nx, int ny) : x(nx), y(ny) {}
	IntPoint(const IntPoint &p) : x(p.x), y(p.y) {}

	inline IntPoint& operator=(const IntPoint& other);

	inline IntPoint& operator+=(const IntPoint& other);
	inline IntPoint& operator-=(const IntPoint& other);
	inline IntPoint& operator*=(int scale);
	inline IntPoint& operator/=(int divisor);
	inline IntPoint& operator/=(const IntPoint& other);

	inline IntPoint operator+(const IntPoint& other) const;
	inline IntPoint operator-(const IntPoint& other) const;
	inline IntPoint operator*(int scale) const;
	inline IntPoint operator/(int divisor) const;
	inline IntPoint operator/(const IntPoint& other) const;

	inline bool operator==(const IntPoint& other) const;
	inline bool operator!=(const IntPoint& other) const;

	int x = 0;
	int y = 0;
};

inline bool IntPoint::operator==(const IntPoint& other) const
{
	return x == other.x && y == other.y;
}

inline bool IntPoint::operator!=(const IntPoint& other) const
{
	return x != other.x || y != other.y;
}

inline IntPoint& IntPoint::operator*=(int scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

inline IntPoint& IntPoint::operator/=(int divisor)
{
	x /= divisor;
	y /= divisor;
	return *this;
}

inline IntPoint& IntPoint::operator+=(const IntPoint& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

inline IntPoint& IntPoint::operator-=(const IntPoint& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

inline IntPoint& IntPoint::operator/=(const IntPoint& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

inline IntPoint& IntPoint::operator=(const IntPoint& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

inline IntPoint IntPoint::operator*(int scale) const
{
	return IntPoint(*this) *= scale;
}

inline IntPoint IntPoint::operator/(int divisor) const
{
	return IntPoint(*this) /= divisor;
}

inline IntPoint IntPoint::operator+(const IntPoint& other) const
{
	return IntPoint(*this) += other;
}

inline IntPoint IntPoint::operator-(const IntPoint& other) const
{
	return IntPoint(*this) -= other;
}

inline IntPoint IntPoint::operator/(const IntPoint& other) const
{
	return IntPoint(*this) /= other;
}