#include "stdafx.h"
#if GAME_MICRO_ROGUE
#include "MicroGraphics.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "OGLFunc.h"

void MicroGraphics::Init()
{
	m_shaders = ShaderManager::Get().LoadShader("simple", "../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr);

	TextureManager::Get().LoadTexture("floor", "../data/textures/floor1.png", true);

	recta = DrawSprite(0, 0, 128, 128, { 255,0, 255, 255 }, TextureManager::Get().GetTexture("floor"));

	grid = DrawGrid(0, 0, 256, 256, 32, { 255,0, 255, 255 });

	if (recta.drawType == DrawType::Points)
		spriteMesh.SetDrawType(GL_POINTS);
	if (recta.drawType == DrawType::Lines)
		spriteMesh.SetDrawType(GL_LINES);
	if (recta.drawType == DrawType::Triangles)
		spriteMesh.SetDrawType(GL_TRIANGLES);

	spriteMesh.SetDrawType(GL_LINES);
	spriteMesh.SetVertices(recta.vertices);
	spriteMesh.SetIndexes(recta.indexes);
}

void MicroGraphics::Render(Camera2D& camera)
{
	m_shaders->Bind();
	m_shaders->SetMatrix4("MVP", camera.GetMatrix());
	recta.texture->Bind(0);
	spriteMesh.Draw();
}

void MicroGraphics::Close()
{
	spriteMesh.Destroy();
}

#endif