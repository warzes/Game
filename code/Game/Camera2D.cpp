#include "stdafx.h"
#include "Camera2D.h"
//-----------------------------------------------------------------------------
Camera2D::Camera2D(float screenWidth, float screenHeight, float scale, float speed)
{
	m_scrDim.x = screenWidth;
	m_scrDim.y = screenHeight;
	m_scale = scale;
	m_speed = speed;
	m_dirty = true;
}
//-----------------------------------------------------------------------------
void Camera2D::SetPos(float x, float y)
{
	if (m_pos.x != x || m_pos.y != y)
	{
		m_pos.x = x;
		m_pos.y = y;
		m_dirty = true;
	}	
}
//-----------------------------------------------------------------------------
void Camera2D::SetPos(const glm::vec2& pos)
{
	if (m_pos != pos)
	{
		m_pos = pos;
		m_dirty = true;
	}
}
//-----------------------------------------------------------------------------
glm::mat4 Camera2D::GetMatrix()
{
	if (m_dirty)
		computeMatrix();
	return m_matrix;
}
//-----------------------------------------------------------------------------
AABB Camera2D::GetAABB()
{
	return AABB(
		(m_pos.x - m_scrDim.x / 2 / m_scale),
		(m_pos.y - m_scrDim.y / 2 / m_scale),
		(m_pos.x + m_scrDim.x / 2 / m_scale),
		(m_pos.y + m_scrDim.y / 2 / m_scale));
}
//-----------------------------------------------------------------------------
void Camera2D::computeMatrix()
{
	glm::mat4 Projection = glm::ortho(0.0f, m_scrDim.x, 0.0f, m_scrDim.y, -1.0f, 1.0f);
	glm::mat4 View = glm::mat4(1);
	glm::mat4 Scale = glm::scale(glm::mat4(1), glm::vec3(m_scale));
	glm::mat4 Translate = glm::translate(
		glm::mat4(1),
		glm::vec3(-m_pos.x * m_scale + m_scrDim.x / 2, -m_pos.y * m_scale + m_scrDim.y / 2, 0));
	glm::mat4 Model = Translate * Scale;

	m_matrix = Projection * View * Model;
	m_dirty = false;
}
//-----------------------------------------------------------------------------