#pragma once

#if GAME_MICRO_RPG

#include "EngineConfig.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera2D.h"
#include "DrawSprite.h"
#include "DrawGrid.h"
#include "RenderBatcher.h"
#include "DrawMultiSprite.h"
#include "Camera2D.h"

class Game
{
public:
	Game();
	~Game();

	EngineConfig InitConfig();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void Close();

private:
	void loadResource();

	std::shared_ptr<ShaderProgram> m_shaders;
	DrawSprite recta;
	DrawMultiSprite mSprite;
	RenderBatcher batcher;
	Camera2D m_mainCamera;
};

#endif
