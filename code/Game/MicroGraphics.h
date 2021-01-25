#pragma once

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera2D.h"

class MicroGraphics
{
public:
	void Init();
	void Render(Camera2D &camera);
	void Close();

private:
	std::shared_ptr<ShaderProgram> m_shaders;
	Mesh spriteMesh;
};