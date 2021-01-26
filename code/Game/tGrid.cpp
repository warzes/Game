#include "stdafx.h"
#if EXAMPLE_TEST
#include "tGrid.h"
//-----------------------------------------------------------------------------
Grid::Grid(float x, float y, float width, float height, int step, const Color& color)
	: mX(x)
	, mY(y)
	, mWidth(width)
	, mHeight(height)
	, mStep(step)
	, mColor(color)
{
	vertices.resize(1 + 2 * (int)(width + height) / step);
	indexes.resize(1 + 2 * (int)(width + height) / step);
	drawType = DrawType::Lines;

	buildVertices();
}
//-----------------------------------------------------------------------------
void Grid::buildVertices()
{
	int i = 0;

	for (int x = 0; x < (int)mWidth; x += mStep) 
	{
		vertices[i].SetPos(x, 0, m_z);
		vertices[i].SetColor(mColor);
		indexes[i] = i;
		i++;
		vertices[i].SetPos(x, mHeight, m_z);
		vertices[i].SetColor(mColor);
		indexes[i] = i;
		i++;
	}

	for (int y = 0; y < (int)mHeight; y += mStep) 
	{
		vertices[i].SetPos(0, y, m_z);
		vertices[i].SetColor(mColor);
		indexes[i] = i;
		i++;
		vertices[i].SetPos(mWidth, y, m_z);
		vertices[i].SetColor(mColor);
		indexes[i] = i;
		i++;
	}
}
//-----------------------------------------------------------------------------
#endif