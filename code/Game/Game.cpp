#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Engine.h"

Sprite* sprite;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto& engineConfig = GetEngine().GetConfig();

	ResourceManager::LoadShader("../data/shaders/sprite.vs", "../data/shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(engineConfig.window.width),
		static_cast<float>(engineConfig.window.height), 0.0f, -1.0f, 1.0f);


	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	sprite = new Sprite(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("../data/image/test.png", true, "face");
}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
	sprite->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Game::Close()
{
	ResourceManager::Clear();
}