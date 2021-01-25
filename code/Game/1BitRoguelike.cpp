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

    m_mainCamera = Camera2D(width, height, 1.0f, 1.001f);

    m_graphics.Init();
}


void Game::Update(float dt)
{
    auto width = GetEngine().GetConfig().window.width;
    auto height = GetEngine().GetConfig().window.height;
    m_mainCamera.SetScrDim(width, height);
    m_mainCamera.SetPos(0, 0);
    m_mainCamera.SetScale(1.0f);
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
    m_graphics.Render(m_mainCamera);
}

void Game::Close()
{
    m_graphics.Close();
}