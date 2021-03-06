#pragma once

#if EXAMPLE_TEST

#include "EngineConfig.h"
#include "ShaderProgram.h"
#include "RenderBatcher.h"
#include "tPlayer.h"
#include "Camera2D.h"

class Game
{
public:
	Game();
	~Game();

	EngineConfig InitConfig();

	static Game& Get();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void Close();

	std::vector<Entity*>& GetEntities() { return mEntities; }

private:
	std::shared_ptr<ShaderProgram> shader;
	RenderBatcher mRenderer;

	Player* mPlayer;
	Camera2D mCamera;
	std::vector<Entity*> mEntities;

	unsigned mMapX, mMapY;

	void CameraUpdate(float dt);
	void buildMap();
};

#endif