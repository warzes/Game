#include "stdafx.h"
#if GAME_MICRO_RPG
#include "MicroRPG.h"
#include "Engine.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "OGLFunc.h"
#include "Keyboard.h"
//-----------------------------------------------------------------------------
EngineConfig Game::InitConfig()
{
    EngineConfig config;
    config.graphics.ClearColor = {0,0,0,0};
    config.window.width = 640;
    config.window.height = 480;
    return config;
}
//-----------------------------------------------------------------------------
Game::Game()
{
}
//-----------------------------------------------------------------------------
Game::~Game()
{
}
//-----------------------------------------------------------------------------
void Game::Init()
{
    auto width = GetEngine().GetConfig().window.width;
    auto height = GetEngine().GetConfig().window.height;

    loadResource();

    m_mainCamera = Camera2D(width, height, 1.0f, 1.001f);
      

    batcher.Init();

    for (int x = -16; x < 16; x++)
    {
        for (int y = -8; y < 8; y++)
        {
            auto recta = new DrawSprite(x*20, y*28, 20, 28, { 255,255, 255, 255 }, TextureManager::Get().GetTexture("mar"));
            batcher.Add(recta);
        }
    }

    
}
//-----------------------------------------------------------------------------
void Game::Update(float dt)
{
    auto width = GetEngine().GetConfig().window.width;
    auto height = GetEngine().GetConfig().window.height;

    auto idealWidth = 480.0f* width/ height;
    auto idealHeight = 480.0f;
    m_mainCamera.SetScrDim(idealWidth, idealHeight);

    std::cout << height << std::endl;

    static float x = 0;

    if (Keyboard::Get().KeyDown(Keyboard::KEY_A))
        x -= 50.0f * dt;
    if (Keyboard::Get().KeyDown(Keyboard::KEY_D))
        x += 50.0f * dt;

    //int tx = x; // округляем

    m_mainCamera.SetPos(x, 0);
    m_mainCamera.SetScale(1.0f);
}
//-----------------------------------------------------------------------------
void Game::ProcessInput(float dt)
{
}
//-----------------------------------------------------------------------------
void Game::Render()
{
    m_shaders->Bind();
    m_shaders->SetMatrix4("MVP", m_mainCamera.GetMatrix());

    batcher.Draw();
}
//-----------------------------------------------------------------------------
void Game::Close()
{
}
//-----------------------------------------------------------------------------
void Game::loadResource()
{
    m_shaders = ShaderManager::Get().LoadShader("simple", "../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr);
    TextureManager::Get().LoadTexture("floor", "../data/textures/floor1.png", true);
    TextureManager::Get().LoadTexture("hero", "../data/textures/hero.png", true);
    TextureManager::Get().LoadTexture("mar", "../data/textures/mar.png", true);
}
//-----------------------------------------------------------------------------
#endif