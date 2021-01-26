#include "stdafx.h"
#if GAME_MICRO_ROGUE
#include "MicroGraphics.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "OGLFunc.h"

//дальше делать rectangleMesh, FilledRectangleMesh, SpriteMesh

void MicroGraphics::Init()
{
	m_shaders = ShaderManager::Get().LoadShader("simple", "../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr);

	TextureManager::Get().LoadTexture("floor", "../data/textures/floor1.png", true);

	recta = DrawRectangle(0, 0, 128, 128, { 255,0,255,255 });

	//enum
	//{
	//	LB,
	//	LT,
	//	RT,
	//	RB
	//};
	//AABB m_UV = { 0, 0, 1, 1 };
	//std::vector<int> Indexes = { LB, LT, RT, RT, RB, LB };
	//std::vector<Vertex3PCT> Vertices;
	//Vertices.resize(4);



	//Vertices[LB].SetPos(0, 0, 0);
	//Vertices[LT].SetPos(0, 0 + 32, 0);
	//Vertices[RT].SetPos(0 + 32, 0 + 32, 0);
	//Vertices[RB].SetPos(0 + 32, 0, 0);

	//for (size_t i = 0; i < Vertices.size(); i++)
	//	Vertices[i].SetColor({255,255,255,255});

	//Vertices[LB].SetUV(m_UV.minX, m_UV.minY);
	//Vertices[LT].SetUV(m_UV.minX, m_UV.maxY);
	//Vertices[RT].SetUV(m_UV.maxX, m_UV.maxY);
	//Vertices[RB].SetUV(m_UV.maxX, m_UV.minY);

	spriteMesh.SetDrawType(GL_LINES);
	spriteMesh.SetVertices(recta.vertices);
	spriteMesh.SetIndexes(recta.indexes);
}

void MicroGraphics::Render(Camera2D& camera)
{
	m_shaders->Bind();
	m_shaders->SetMatrix4("MVP", camera.GetMatrix());

	//TextureManager::Get().GetTexture("floor")->Bind(0);
	spriteMesh.Draw();
}

void MicroGraphics::Close()
{
	spriteMesh.Destroy();
}

#endif