#pragma once

#if EXAMPLE_TEST

#include "ShaderProgram.h"
#include "Renderer.h"
#include "Player.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();

	static Game& Get();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void Close();

	std::vector<Entity*>& GetEntities() { return mEntities; }

private:
	ShaderProgram shader;
	Renderer mRenderer;

	Player* mPlayer;
	Camera mCamera;
	std::vector<Entity*> mEntities;

	unsigned mMapX, mMapY;

	void CameraUpdate(float dt);
	void buildMap();
};

#endif