#include "stdafx.h"
#include "RenderBatcher.h"
#include "OGLFunc.h"
//-----------------------------------------------------------------------------
RenderBatcher::~RenderBatcher()
{
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}
//-----------------------------------------------------------------------------
void RenderBatcher::Init()
{
	enum shader_attrs 
	{
		POSITION,
		COLOR,
		UV,
		SHADER_NUM_ATTRS
	};

	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(UV);

	glVertexAttribPointer(
		POSITION, sizeof(m_vertices[0].pos) / sizeof(float), GL_FLOAT, GL_FALSE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, pos));

	glVertexAttribPointer(
		COLOR, sizeof(m_vertices[0].color) / sizeof(uint8_t), GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, color));

	glVertexAttribPointer(
		UV, sizeof(m_vertices[0].uv) / sizeof(float), GL_FLOAT, GL_FALSE,
		sizeof(m_vertices[0]), (void*)offsetof(Vertex3PCT, uv));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
//-----------------------------------------------------------------------------
void RenderBatcher::Add(Renderable* renderable)
{
	m_queue.push_back(renderable);
	m_dirty = true;
}
//-----------------------------------------------------------------------------
bool RenderBatcher::Delete(Renderable* renderable)
{
	auto it = std::remove(m_queue.begin(), m_queue.end(), renderable);
	if (it != m_queue.end())
	{
		m_queue.erase(it);
		m_dirty = true;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
void RenderBatcher::Clear()
{
	m_vertices.clear();
	m_indexes.clear();
	m_batches.clear();
	m_queue.clear();
}
//-----------------------------------------------------------------------------
void RenderBatcher::Draw()
{
	if (m_dirty)
	{
		sortQueue();
		BuildBatches();
	}		
	else
		RebuildVertices();

	glBindVertexArray(m_vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexes.size() * sizeof(m_indexes[0]), &m_indexes[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	for (unsigned i = 0; i < m_batches.size(); i++)
	{
		GLuint drawType;
		switch (m_batches[i].drawType)
		{
		case DrawType::Points:
			drawType = GL_POINTS;
			break;
		case DrawType::Lines:
			drawType = GL_LINES;
			break;
		case DrawType::Triangles:
			drawType = GL_TRIANGLES;
			break;
		default:
			return;
		}
		m_batches[i].texture->Bind(0);
		glDrawElements(drawType, m_batches[i].numIndexes, GL_UNSIGNED_INT, (void*)(m_batches[i].indexOffs * sizeof(int)));
	}
}
//-----------------------------------------------------------------------------
void RenderBatcher::BuildBatches()
{
	m_vertices.clear();
	m_indexes.clear();
	m_batches.clear();

	DrawType lastDrawType = DrawType::None;
	std::shared_ptr<Texture2D> lastTexture = nullptr;
	unsigned verticesOffs = 0, indexesOffs = 0;
	RenderBatch* batch = nullptr;

	for (unsigned i = 0; i < m_queue.size(); i++)
	{
		if (lastDrawType != m_queue[i]->drawType || lastTexture != m_queue[i]->texture)
		{
			lastDrawType = m_queue[i]->drawType;
			lastTexture = m_queue[i]->texture;
			batch = getBatch(lastDrawType, lastTexture, verticesOffs, indexesOffs);
		}

		unsigned indexGOffs = m_vertices.size();
		m_vertices.insert(m_vertices.end(), m_queue[i]->vertices.begin(), m_queue[i]->vertices.end());

		verticesOffs += m_queue[i]->vertices.size();
		batch->numVertices += m_queue[i]->vertices.size();

		for (unsigned j = 0; j < m_queue[i]->indexes.size(); j++)
		{
			m_indexes.emplace_back(indexGOffs + m_queue[i]->indexes[j]);
		}
		indexesOffs += m_queue[i]->indexes.size();
		batch->numIndexes += m_queue[i]->indexes.size();
	}
	m_dirty = false;
}
//-----------------------------------------------------------------------------
void RenderBatcher::RebuildVertices()
{
	m_vertices.clear();
	for (unsigned i = 0; i < m_queue.size(); i++)
	{
		for (unsigned j = 0; j < m_queue[i]->vertices.size(); j++)
		{
			m_vertices.emplace_back(m_queue[i]->vertices[j]);
		}
	}
}
//-----------------------------------------------------------------------------
RenderBatch* RenderBatcher::getBatch(DrawType drawType, std::shared_ptr<Texture2D> tex, unsigned verticesOffs, unsigned indexesOffs)
{
	RenderBatch batch(verticesOffs, indexesOffs, drawType, tex);
	auto it = std::find(m_batches.begin(), m_batches.end(), batch);

	if (it == m_batches.end())
	{
		RenderBatch batch(verticesOffs, indexesOffs, drawType, tex);
		m_batches.push_back(batch);
		return &m_batches.back();
	}

	return &(*it);
}
//-----------------------------------------------------------------------------
void RenderBatcher::printBatches()
{
	for (unsigned i = 0; i < m_batches.size(); i++) 
	{
		std::cout << "dtype: " << (m_batches[i].drawType == DrawType::Lines ? "lines" : "triangles")
			<< ", texture id: " << m_batches[i].texture->ID
			<< ", verticesOffs: " << m_batches[i].verticesOffs
			<< ", numVertices: " << m_batches[i].numVertices
			<< ", indexOffs: " << m_batches[i].indexOffs
			<< ", numIndexes: " << m_batches[i].numIndexes
			<< std::endl;
	}
}
//-----------------------------------------------------------------------------
void RenderBatcher::sortQueue()
{
	std::sort(m_queue.begin(), m_queue.end(), [](Renderable* a, Renderable* b){return a->texture->ID < b->texture->ID;});
}
//-----------------------------------------------------------------------------