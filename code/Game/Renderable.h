#pragma once

#include "Vertex.h"
#include "Texture2D.h"

enum class DrawType
{
	None,
	Points,
	Lines,
	Triangles,
};

class Renderable
{
public:
	std::vector<Vertex3PCT> vertices;
	std::vector<int> indexes;
	DrawType drawType = DrawType::None;
	std::shared_ptr<Texture2D> texture = nullptr;
};