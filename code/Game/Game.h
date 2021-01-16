#pragma once

#include "GameLevel.h"

enum class GameState 
{
    Active,
    Menu,
    Win
};

// Represents the four possible (collision) directions
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
// Defines a Collision typedef that represents collision data
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

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

    void DoCollisions();
    // reset
    void ResetLevel();
    void ResetPlayer();

    GameState State = GameState::Active;

    std::vector<GameLevel> Levels;
    unsigned int           Level;
};