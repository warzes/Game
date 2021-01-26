#include "stdafx.h"
#if EXAMPLE_TEST
#include "tFilledRectangle.h"
//-----------------------------------------------------------------------------
FilledRectangle::FilledRectangle(float x, float y, float width, float height, const Color& color)
{
	vertices.resize(4);
	indexes = { LB, LT, RT, RT, RB, LB };
	drawType = DrawType::Triangles;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_color = color;

	buildVertices();
}
//-----------------------------------------------------------------------------
#endif