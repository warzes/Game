#pragma once

#if EXAMPLE_TEST

#include "Rectangle.h"
#include "tVertex.h"

struct RenderBatch {
    unsigned verticesOffs,
        numVertices; // offset in vertices buffer, number of vertices
    unsigned indexOffs, numIndexes; // offset in index buffer, number of indexes
    DrawType drawType; // draw type
    GLuint textureId; // textureId if applicable

    RenderBatch() { textureId = 0; }

    RenderBatch(unsigned verticesOffs, unsigned indexOffs, DrawType drawType, GLuint textureId)
        : verticesOffs(verticesOffs)
        , numVertices(0)
        , indexOffs(indexOffs)
        , numIndexes(0)
        , drawType(drawType)
        , textureId(textureId)
    {
    }
    bool operator==(const RenderBatch& other)
    {
        return this->drawType == other.drawType && this->textureId == other.textureId;
    }
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    void Init();
    void Add(tRenderable* renderable);
    bool Delete(tRenderable* renderable);
    void Clear();
    void Draw();
    void BuildBatches();
    void RebuildVertices();

private:
    GLuint mVertexArray, mVertexBuffer, mIndexBuffer;
    std::vector<Vertex3PCT> mVertices;
    std::vector<int> mIndexes;
    std::vector<tRenderable*> mQueue;
    std::vector<RenderBatch> mBatches;
    bool mDirty;

    RenderBatch* GetBatch(DrawType draqType, GLuint textureId, unsigned verticesOffs, unsigned indexesOffs);
    void PrintBatches();
};

#endif