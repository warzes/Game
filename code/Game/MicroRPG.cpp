#include "stdafx.h"
#if GAME_MICRO_RPG
#include "MicroRPG.h"
#include "Engine.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "OGLFunc.h"

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

    m_shaders = ShaderManager::Get().LoadShader("simple", "../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr);
    TextureManager::Get().LoadTexture("floor", "../data/textures/floor1.png", true);
    TextureManager::Get().LoadTexture("hero", "../data/textures/hero.png", true);

    batcher.Init();

    recta = DrawSprite(0, 0, 128, 128, { 255,0, 255, 255 }, TextureManager::Get().GetTexture("floor"));

    mSprite = DrawMultiSprite(128, 128, TextureManager::Get().GetTexture("hero"));
    mSprite.SetPos(0, 0);
    mSprite.SetNumFrames(3, 4);
    mSprite.SetFrame(1, 2);

    batcher.Add(&recta);
    batcher.Add(&mSprite);
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
    m_shaders->Bind();
    m_shaders->SetMatrix4("MVP", m_mainCamera.GetMatrix());

    batcher.Draw();
}

void Game::Close()
{
}

#endif