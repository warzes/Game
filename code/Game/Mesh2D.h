#pragma once

#include "Vertex.h"

// TODO; refactor

class Mesh
{
public:
	Mesh();
	~Mesh();
	void AddVertex(const Vertex2PCT& vertex);
	void AddIndex(const int index);
	void SetVertices(const std::vector<Vertex2PCT>& vertices);
	void SetIndexes(const std::vector<int>& indexes);
	void SetDrawType(GLenum drawType);
	void SetProgramId(GLuint progrmId);
	virtual void Draw();

protected:
	bool mDirty;
	std::vector<Vertex2PCT> mVertices;
	std::vector<int> mIndexes;
	GLenum mDrawType;
	GLuint mVertexArray, mVertexBuffer, mIndexBuffer;
	GLuint mProgramId;

private:
	void Update();
};