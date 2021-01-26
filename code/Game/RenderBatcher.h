#pragma once

#include "Renderable.h"
#include "Vertex.h"

struct RenderBatch 
{	
	RenderBatch() { texture = nullptr; }
	RenderBatch(unsigned inVerticesOffs, unsigned inIndexOffs, DrawType inDrawType, std::shared_ptr<Texture2D> inTexture = nullptr)
		: verticesOffs(inVerticesOffs)
		, numVertices(0)
		, indexOffs(inIndexOffs)
		, numIndexes(0)
		, drawType(inDrawType)
		, texture(inTexture)
	{
	}
	bool operator==(const RenderBatch& other)
	{
		return this->drawType == other.drawType && this->texture == other.texture;
	}

	unsigned verticesOffs = 0;               // offset in vertices buffer,
	unsigned numVertices = 0;                // number of vertices
	unsigned indexOffs = 0;                  // offset in index buffer
	unsigned numIndexes = 0;                 // number of indexes
	DrawType drawType = DrawType::Triangles; // draw type
	std::shared_ptr<Texture2D> texture;      // textureId if applicable
};

class RenderBatcher 
{
public:
	~RenderBatcher();

	void Init();
	void Add(Renderable* renderable);
	bool Delete(Renderable* renderable);
	void Clear();
	void Draw();
	void BuildBatches();
	void RebuildVertices();

private:
	RenderBatch* getBatch(DrawType draqType, std::shared_ptr<Texture2D> tex, unsigned verticesOffs, unsigned indexesOffs);
	void printBatches();
	void sortQueue();

	GLuint m_vertexArray = 0;
	GLuint m_vertexBuffer = 0;
	GLuint m_indexBuffer = 0;
	std::vector<Vertex3PCT> m_vertices;
	std::vector<int> m_indexes;

	std::vector<Renderable*> m_queue;
	std::vector<RenderBatch> m_batches;

	bool m_dirty = true;
};