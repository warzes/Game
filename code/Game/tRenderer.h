#pragma once

#if EXAMPLE_TEST

#include"Renderable.h"
#include "Vertex.h"

struct RenderBatch {
    unsigned verticesOffs,
        numVertices; // offset in vertices buffer, number of vertices
    unsigned indexOffs, numIndexes; // offset in index buffer, number of indexes
    DrawType drawType; // draw type
    std::shared_ptr<Texture2D> texture; // textureId if applicable

    RenderBatch() { texture = nullptr; }

    RenderBatch(unsigned verticesOffs, unsigned indexOffs, DrawType drawType, std::shared_ptr<Texture2D> inTexture)
        : verticesOffs(verticesOffs)
        , numVertices(0)
        , indexOffs(indexOffs)
        , numIndexes(0)
        , drawType(drawType)
        , texture(inTexture)
    {
    }
    bool operator==(const RenderBatch& other)
    {
        return this->drawType == other.drawType && this->texture == other.texture;
    }
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    void Init();
    void Add(Renderable* renderable);
    bool Delete(Renderable* renderable);
    void Clear();
    void Draw();
    void BuildBatches();
    void RebuildVertices();

private:
    GLuint mVertexArray, mVertexBuffer, mIndexBuffer;
    std::vector<Vertex3PCT> mVertices;
    std::vector<int> mIndexes;
    std::vector<Renderable*> mQueue;
    std::vector<RenderBatch> mBatches;
    bool mDirty;

    RenderBatch* GetBatch(DrawType draqType, std::shared_ptr<Texture2D> tex, unsigned verticesOffs, unsigned indexesOffs);
    void PrintBatches();
};

#endif