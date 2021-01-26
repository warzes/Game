#pragma once

#if GAME_MICRO_ROGUE

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera2D.h"
#include "DrawSprite.h"

class MicroGraphics
{
public:
	void Init();
	void Render(Camera2D &camera);
	void Close();

private:
	std::shared_ptr<ShaderProgram> m_shaders;
	Mesh spriteMesh;
	DrawSprite recta;
};

#endif