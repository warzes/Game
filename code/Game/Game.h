#pragma once

enum class GameState 
{
    Active,
    Menu,
    Win
};

class Game
{
public:
    Game();
    ~Game();

    void Init();

    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    GameState State = GameState::Active;
};