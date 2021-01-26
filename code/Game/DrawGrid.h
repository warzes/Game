#pragma once

#include "Renderable.h"
#include "AABB.h"

// TODO: ��������� �� ���� ������, � ���-�� ����� � �� ������
// TODO: ��������� ����� �� ��������

class DrawGrid : public Renderable
{
public:
	DrawGrid() {}
	DrawGrid(float x, float y, float width, float height, int step, const Color& color);

private:
	void buildVertices();

	float m_x = 0.0f, m_y = 0.0f, m_width = 0.0f, m_height = 0.0f;
	float m_z = 0.0f; // TODO: ���� �����
	int m_step = 0;
	Color m_color;
};