#include "stdafx.h"
#include "1BitRoguelike.h"
#include "Engine.h"

EngineConfig Game::InitConfig()
{
    EngineConfig config;

    //config.graphics.ClearColor = {0,0,0,0};

    return config;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    auto width = GetEngine().GetConfig().window.width;
    auto height = GetEngine().GetConfig().window.height;
}


void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
}

void Game::Close()
{
}