#include "stdafx.h"
#if EXAMPLE_TEST
#include "tCamera.h"
#include "OGLFunc.h"
//-----------------------------------------------------------------------------
tCamera::tCamera(float screenWidth, float screenHeight, float scale, float speed)
{
	m_ScrDim.x = screenWidth;
	m_ScrDim.y = screenHeight;
	m_Scale = scale;
	m_Speed = speed;
	m_Dirty = true;
}
//-----------------------------------------------------------------------------
void tCamera::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Dirty = true;
}
//-----------------------------------------------------------------------------
void tCamera::SetPos(const glm::vec2& pos)
{
	m_Pos = pos;
	m_Dirty = true;
}
//-----------------------------------------------------------------------------
glm::mat4 tCamera::GetMatrix()
{
	if (m_Dirty)
		computeMatrix();
	return m_Matrix;
}
//-----------------------------------------------------------------------------
void tCamera::SetMatrix(unsigned int programId, const std::string& name)
{
	glUseProgram(programId);
	// TODO:  delete?
	GLint pLoc = glGetUniformLocation(programId, name.c_str());
	if (m_Dirty)
		computeMatrix();
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &m_Matrix[0][0]);
}
//-----------------------------------------------------------------------------
AABB tCamera::GetAABB()
{
	return AABB(
		(m_Pos.x - m_ScrDim.x / 2 / m_Scale),
		(m_Pos.y - m_ScrDim.y / 2 / m_Scale),
		(m_Pos.x + m_ScrDim.x / 2 / m_Scale),
		(m_Pos.y + m_ScrDim.y / 2 / m_Scale));
}
//-----------------------------------------------------------------------------
void tCamera::computeMatrix()
{
	glm::mat4 Projection = glm::ortho(0.0f, m_ScrDim.x, 0.0f, m_ScrDim.y, -1.0f, 1.0f);
	glm::mat4 View = glm::mat4(1);
	glm::mat4 Scale = glm::scale(glm::mat4(1), glm::vec3(m_Scale));
	glm::mat4 Translate = glm::translate(
		glm::mat4(1),
		glm::vec3(-m_Pos.x * m_Scale + m_ScrDim.x / 2, -m_Pos.y * m_Scale + m_ScrDim.y / 2, 0));
	glm::mat4 Model = Translate * Scale;

	m_Matrix = Projection * View * Model;
	m_Dirty = false;
}
//-----------------------------------------------------------------------------
#endif