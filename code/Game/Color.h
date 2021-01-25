#pragma once

class Color;

class LinearColor
{

public:
	static const LinearColor White;
	static const LinearColor Gray;
	static const LinearColor Black;
	static const LinearColor Transparent;
	static const LinearColor Red;
	static const LinearColor Green;
	static const LinearColor Blue;
	static const LinearColor Yellow;

	LinearColor() = default;
	explicit LinearColor(const Color& Color);
	constexpr LinearColor(float inR, float inG, float inB, float inA = 1.0f)
		: r(inR)
		, g(inG)
		, b(inB)
		, a(inA)
	{
	}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;
};

class Color
{
public:
	static const Color White;
	static const Color Black;
	static const Color Transparent;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Cyan;
	static const Color Magenta;
	static const Color Orange;
	static const Color Purple;
	static const Color Turquoise;
	static const Color Silver;
	static const Color Emerald;

	Color() = default;
	constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha)
	{
	}

	LinearColor ReinterpretAsLinear() const
	{
		return LinearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}

	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;
};