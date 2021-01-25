#pragma once

#include "Vertex.h"

class Mesh
{
public:
	void AddVertex(const Vertex3PCT& vertex);
	void AddIndex(const int index);
	void SetVertices(const std::vector<Vertex3PCT>& vertices);
	void SetIndexes(const std::vector<int>& indexes);
	void SetDrawType(GLenum drawType);

	void Draw();

	void Destroy();

private:
	void update();

	std::vector<Vertex3PCT> m_vertices;
	std::vector<int> m_indexes;
	GLenum m_drawType = GL_LINES;
	GLuint m_vertexArray = 0, m_vertexBuffer = 0, m_indexBuffer = 0;
	bool m_dirty = true;
};