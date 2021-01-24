#pragma once

#if EXAMPLE_BREAKOUT

#include "GameLevel.h"
#include "PowerUp.h"

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
    // powerups
    void SpawnPowerUps(Breakout::GameObject& block);
    void UpdatePowerUps(float dt);

    GameState State = GameState::Active;

    std::vector<Breakout::GameLevel> Levels;
    std::vector<Breakout::PowerUp>   PowerUps;
    unsigned int           Level;

    unsigned int Lives = 3;
};

#endif