#include "stdafx.h"
#include "DrawGrid.h"
//-----------------------------------------------------------------------------
DrawGrid::DrawGrid(float x, float y, float width, float height, int step, const Color& color)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
	, m_step(step)
	, m_color(color)
{
	vertices.resize(1 + 2 * (int)(width + height) / step);
	indexes.resize (1 + 2 * (int)(width + height) / step);
	drawType = DrawType::Lines;

	buildVertices();
}
//-----------------------------------------------------------------------------
void DrawGrid::buildVertices()
{
	int i = 0;

	for (int x = 0; x < (int)m_width; x += m_step) 
	{
		vertices[i].SetPos(x, 0, m_z);
		vertices[i].SetColor(m_color);
		indexes[i] = i;
		i++;
		vertices[i].SetPos(x, m_height, m_z);
		vertices[i].SetColor(m_color);
		indexes[i] = i;
		i++;
	}

	for (int y = 0; y < (int)m_height; y += m_step) 
	{
		vertices[i].SetPos(0, y, m_z);
		vertices[i].SetColor(m_color);
		indexes[i] = i;
		i++;
		vertices[i].SetPos(m_width, y, m_z);
		vertices[i].SetColor(m_color);
		indexes[i] = i;
		i++;
	}
}
//-----------------------------------------------------------------------------