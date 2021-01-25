#pragma once

#include "EngineConfig.h"
#include "MicroGraphics.h"
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
	MicroGraphics m_graphics;
	Camera2D m_mainCamera;
};
