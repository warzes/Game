#pragma once

#include "Vertex.h"

/*
EXAMPLE
	//--------------------------------
	DrawSprite sprite;
	Mesh spriteMesh;
	//--------------------------------
	sprite = DrawSprite(0, 0, 128, 128, { 255,0, 255, 255 }, TextureManager::Get().GetTexture("sprite"));
	spriteMesh.SetDrawType(GL_TRIANGLES);
	spriteMesh.SetVertices(sprite.vertices);
	spriteMesh.SetIndexes(sprite.indexes);
	//--------------------------------
	m_shaders->Bind();
	m_shaders->SetMatrix4("MVP", camera.GetMatrix());
	sprite.texture->Bind(0);
	spriteMesh.Draw();
	//--------------------------------
	spriteMesh.Destroy();
*/

class Mesh
{
public:
	void AddVertex(const Vertex3PCT& vertex);
	void AddIndex(const int index);
	void SetVertices(const std::vector<Vertex3PCT>& vertices);
	void SetIndexes(const std::vector<int>& indexes);
	void SetDrawType(GLenum drawType);
	void ClearData(bool vertex = true, bool index = true);

	void Draw();

	void Destroy();

	size_t GetVertexNum() const { return m_vertices.size(); }

//private:
	void update();

	std::vector<Vertex3PCT> m_vertices;
	std::vector<int> m_indexes;
	GLenum m_drawType = GL_LINES;
	GLuint m_vertexArray = 0;
	GLuint m_vertexBuffer = 0;
	GLuint m_indexBuffer = 0;
	bool m_dirty = true;
};