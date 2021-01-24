#pragma once

class Game
{
public:
	Game();
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	void Close();
};