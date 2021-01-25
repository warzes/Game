#pragma once

#include "EngineConfig.h"

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
};
