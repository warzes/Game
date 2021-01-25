#include "stdafx.h"
#if EXAMPLE_TEST
#include "FilledRectangle.h"
//-----------------------------------------------------------------------------
FilledRectangle::FilledRectangle(float x, float y, float width, float height, const Color& color)
{
	Vertices.resize(4);
	Indexes = { LB, LT, RT, RT, RB, LB };
	DrawType = D_TRIANGLES;
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
	m_Color = color;

	buildVertices();
}
//-----------------------------------------------------------------------------
#endif