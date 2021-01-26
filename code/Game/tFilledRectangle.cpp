#include "stdafx.h"
#if EXAMPLE_TEST
#include "tFilledRectangle.h"
//-----------------------------------------------------------------------------
FilledRectangle::FilledRectangle(float x, float y, float width, float height, const Color& color)
{
	vertices.resize(4);
	indexes = { LB, LT, RT, RT, RB, LB };
	drawType = DrawType::Triangles;
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
	m_Color = color;

	buildVertices();
}
//-----------------------------------------------------------------------------
#endif