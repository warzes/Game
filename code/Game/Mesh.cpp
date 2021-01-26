#include "stdafx.h"
#include "Mesh.h"
#include "OGLFunc.h"
//-----------------------------------------------------------------------------
void Mesh::Destroy()
{
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	m_vertexBuffer = m_vertexArray = m_indexBuffer = 0;
}
//-----------------------------------------------------------------------------
void Mesh::SetVertices(const std::vector<Vertex3PCT>& vertices)
{
	m_vertices = vertices;
	m_dirty = true;
}
//-----------------------------------------------------------------------------
void Mesh::SetIndexes(const std::vector<int>& indexes)
{
	m_indexes = indexes;
	m_dirty = true;
}
//-----------------------------------------------------------------------------
void Mesh::SetDrawType(GLenum drawType)
{
	m_drawType = drawType;
}
//-----------------------------------------------------------------------------
void Mesh::AddVertex(const Vertex3PCT& vertex)
{
	m_vertices.push_back(vertex);
	m_dirty = true;
}
//-----------------------------------------------------------------------------
void Mesh::AddIndex(const int index)
{
	m_indexes.push_back(index);
	m_dirty = true;
}
//-----------------------------------------------------------------------------
void Mesh::Draw()
{
	if (m_dirty)
		update();
	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // TODO: ???
	glDrawElements(m_drawType, m_indexes.size(), GL_UNSIGNED_INT, nullptr);
}
//-----------------------------------------------------------------------------
void Mesh::update()
{
	if (m_vertices.empty() || m_indexes.empty())
	{
		glBindVertexArray(0);
		return;
	}		

	enum shader_attrs
	{
		POSITION,
		COLOR,
		UV,
		SHADER_NUM_ATTRS
	};

	if (!m_vertexArray)
	{
		glGenVertexArrays(1, &m_vertexArray);
		glGenBuffers(1, &m_vertexBuffer);
		glGenBuffers(1, &m_indexBuffer);
	}

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(UV);

	// attribute index, number of "coordinates" per vertex (size), type of "coordinate", normalized, stride, pointer
	glVertexAttribPointer(
		POSITION, sizeof(m_vertices[0].pos) / sizeof(float), GL_FLOAT, GL_FALSE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, pos));

	glVertexAttribPointer(
		COLOR, sizeof(m_vertices[0].color) / sizeof(uint8_t), GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, color));

	glVertexAttribPointer(
		UV, sizeof(m_vertices[0].uv) / sizeof(float), GL_FLOAT, GL_FALSE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, uv));

	// Set Data
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], /*GL_STATIC_DRAW*/GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexes.size() * sizeof(m_indexes[0]), &m_indexes[0], /*GL_STATIC_DRAW*/GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_dirty = false;
}
//-----------------------------------------------------------------------------
void Mesh::ClearData(bool vertex, bool index)
{
	if (vertex)
		m_vertices.clear();
	if (index)
		m_indexes.clear();
	m_dirty = true;
}
//-----------------------------------------------------------------------------