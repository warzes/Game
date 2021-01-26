#pragma once

#if EXAMPLE_TEST

#include "EngineConfig.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Player.h"
#include "tCamera.h"

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
	Renderer mRenderer;

	Player* mPlayer;
	tCamera mCamera;
	std::vector<Entity*> mEntities;

	unsigned mMapX, mMapY;

	void CameraUpdate(float dt);
	void buildMap();
};

#endif