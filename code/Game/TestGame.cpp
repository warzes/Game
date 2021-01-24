#include "stdafx.h"
#include "TestGame.h"
#include "Engine.h"
#include "QuadTree.h"
#include "Ball.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include <random>

const int TSZ = 128;
const int BSZ = 32;
const int NUM_BALLS = 200;

class Brick : public Entity 
{
public:
    Brick(float x, float y, float width, float height, unsigned texId)
        : Entity(x, y, width, height)
        , mSprite(width, height, texId)
    {
        m_Type = BRICK;
        mSprite.SetPos(m_Pos);
    }
    Renderable* GetRenderable() { return &mSprite; }

private:
    Sprite mSprite;
};

void Game::buildMap()
{
    std::string map = 
        "####################\n"
        "#                  #\n"
        "#                  #\n"
        "#   ####    ###### #\n"
        "#   #            # #\n"
        "#   ####         # #\n"
        "#   #      ####### #\n"
        "#   ####           #\n"
        "#                  #\n"
        "#    #         #####\n"
        "#                  #\n"
        "#    ##            #\n"
        "#            ###   #\n"
        "#                  #\n"
        "####################\n";

    unsigned x = 0, y = 0;
    mMapX = 0;
    Brick* brick;

    for (unsigned i = 0; i < map.size(); i++) 
    {
        switch (map[i])
        {
        case '#':
            brick = new Brick(x * TSZ, y * TSZ, TSZ, TSZ, TextureManager::GetTexture("background").ID);
            mRenderer.Add(brick->GetRenderable());
            mEntities.push_back(brick);
            x++;
            break;
        case ' ':
            x++;
            break;
        case '\n':
            mMapX = std::max(mMapX, x);
            x = 0;
            y++;
            break;
        default:
            std::cout << "Unknown symbol: " << map[i] << " at " << x << ", " << y;
        }
    }
    mMapY = y;
}

Game* thisGame = nullptr;

Game& Game::Get()
{
    return *thisGame;
}

Game::Game()
{
    thisGame = this;
}

Game::~Game()
{
    thisGame = nullptr;
}

void Game::Init()
{
	auto width = GetEngine().GetConfig().window.width;
	auto height = GetEngine().GetConfig().window.height;

    mCamera = Camera(width, height, 1.0f, 1.001f);

	QuadTree::Test();

    shader = ShaderManager::LoadShader("../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr, "simple");

    TextureManager::LoadTexture("../data/textures/circle.png", true, "circle");
    TextureManager::LoadTexture("../data/textures/brick.png", true, "brick");
    TextureManager::LoadTexture("../data/textures/hero.png", true, "hero");

    mCamera.SetPos(width / 2, height / 2);

    mRenderer.Init();

    buildMap();

    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(1, 255);
    std::normal_distribution<float> fgen(-1, 1);

    // Init balls
    for (int i = 0; i < NUM_BALLS; i++) {
        float radius = BSZ / 2 + gen(rng) % BSZ / 2;

        Ball* ball = new Ball(
            fgen(rng) + (1 + gen(rng) % (mMapX - 2)) * TSZ + radius,
            fgen(rng) + (1 + gen(rng) % (mMapY - 2)) * TSZ + radius,
            radius, TextureManager::GetTexture("circle").ID);

        ball->SetColor(Color(gen(rng), gen(rng), gen(rng), 200));
        ball->SetVelocity(glm::vec2(0.05f * fgen(rng), 0.05f * fgen(rng)));
        // ball->SetVelocity(glm::vec2(0.0001f * fgen(rng), 0.0001f * fgen(rng)));
        mRenderer.Add(ball->GetRenderable());
        mEntities.push_back((Entity*)ball);
    }

    // Player
    mPlayer = new Player(300, 300, 32, 64, TextureManager::GetTexture("player").ID);
    mPlayer->SetSpriteNumFrames(6, 4);
    mRenderer.Add(mPlayer->GetRenderable());
    mEntities.push_back(mPlayer);
}

void Game::CameraUpdate(unsigned ticks)
{
    // float speed = 0.3f * ticks;
    float scaleSpeed = 1.0f + (float)ticks / 1000;

    if (Keyboard::Get().KeyPressed(Keyboard::KEY_Q))
        mCamera.SetScale(mCamera.GetScale() * scaleSpeed);
    else if (Keyboard::Get().KeyPressed(Keyboard::KEY_E))
        mCamera.SetScale(mCamera.GetScale() / scaleSpeed);

    // Follow the player
    mCamera.SetPos(
        mPlayer->GetPos().x + mPlayer->GetWidth() / 2,
        mPlayer->GetPos().y + mPlayer->GetHeight() / 2);

    // Send camera matrix to opengl
    mCamera.SetMatrix(shader.ID, "MVP");
}

void Game::Update(float dt)
{
    for (unsigned i = 0; i < mEntities.size(); i++)
        mEntities[i]->Update(dt);

    CameraUpdate(dt);
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
    mRenderer.Draw();
}

void Game::Close()
{
    for (unsigned i = 0; i < mEntities.size(); i++)
        delete mEntities[i];
}