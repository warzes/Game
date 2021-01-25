#pragma once

#if EXAMPLE_TEST
#include "tVertex.h"

enum DrawType
{
	D_NONE,
	D_POINTS,
	D_LINES,
	D_TRIANGLES,
	D_MAX
};

class tRenderable
{
public:
	std::vector<Vertex3PCT> Vertices;
	std::vector<int> Indexes;
	DrawType DrawType = D_NONE;
	unsigned TextureId = 0;
};
#endif