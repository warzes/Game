#pragma once

class Color
{
public:
	Color() = default;
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha)
	{
	}

	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;
};