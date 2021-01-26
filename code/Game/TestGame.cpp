#include "stdafx.h"
#if EXAMPLE_TEST
#include "TestGame.h"
#include "Engine.h"
#include "QuadTree.h"
#include "Ball.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include <random>

const int TSZ = 64;
const int BSZ = 16;
const int NUM_BALLS = 100;

EngineConfig Game::InitConfig()
{
    EngineConfig config;
    //config.graphics.ClearColor = {0,0,0,0};
    return config;
}

class Brick : public Entity 
{
public:
    Brick(float x, float y, float width, float height, unsigned texId)
        : Entity(x, y, width, height)
        , mSprite(width, height, texId)
    {
        m_Type = BRICK;
        mSprite.SetPos(m_Pos, 1.0f);
    }
    tRenderable* GetRenderable() { return &mSprite; }

private:
    Sprite mSprite;
};

class Floor : public Entity
{
public:
    Floor(float x, float y, float width, float height, unsigned texId)
        : Entity(x, y, width, height)
        , mSprite(width, height, texId)
    {
        m_Type = FLOOR;
        mSprite.SetPos(m_Pos, -1.0);
    }
    tRenderable* GetRenderable() { return &mSprite; }

private:
    Sprite mSprite;
};

void Game::buildMap()
{

    std::string map =
        "####################\n"
        "#                  #\n"
        "#   # # ###  #  #  #\n"
        "#   ### ##   #  #  #\n"
        "#   # # ###  ## ## #\n"
        "#                  #\n"
        "#                  #\n"
        "#    #########     #\n"
        "#            #     #\n"
        "#    #########     #\n"
        "#        #         #\n"
        "#        #         #\n"
        "#        #         #\n"
        "#                  #\n"
        "####################\n";



    unsigned x = 0, y = 0;
    mMapX = 0;
    Brick* brick;
    Floor* floor;
    for (unsigned i = 0; i < map.size(); i++) 
    {
        switch (map[i])
        {
        case '#':
            brick = new Brick(x * TSZ, y * TSZ, TSZ, TSZ, TextureManager::Get().GetTexture("brick")->ID);
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
    // кривой костыль, так как батчинг неправильно заполняется
    {
        x = 0, y = 0;
        for (unsigned i = 0; i < map.size(); i++)
        {
            switch (map[i])
            {
            case '#':
                x++;
                break;
            case ' ':
                floor = new Floor(x * TSZ, y * TSZ, TSZ, TSZ, TextureManager::Get().GetTexture("floor")->ID);
                mRenderer.Add(floor->GetRenderable());
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

    mCamera = tCamera(width, height, 1.0f, 1.001f);

	QuadTree::Test();

    shader = ShaderManager::Get().LoadShader("simple", "../data/shaders/simple.vs", "../data/shaders/simple.fs", nullptr);

    TextureManager::Get().LoadTexture("floor","../data/textures/floor1.png", true);
    TextureManager::Get().LoadTexture("circle", "../data/textures/block.png", true);
    TextureManager::Get().LoadTexture("brick", "../data/textures/brick1.png", true);
    TextureManager::Get().LoadTexture("hero", "../data/textures/hero.png", true);

    mCamera.SetPos(width / 2, height / 2);

    mRenderer.Init();

    buildMap();

    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(1, 255);
    std::normal_distribution<float> fgen(-1, 1);

    // Init balls
    for (int i = 0; i < NUM_BALLS; i++) 
    {
        float radius = BSZ / 2 + gen(rng) % BSZ / 2;

        Ball* ball = new Ball(
            fgen(rng) + (1 + gen(rng) % (mMapX - 2)) * TSZ + radius,
            fgen(rng) + (1 + gen(rng) % (mMapY - 2)) * TSZ + radius,
            radius, TextureManager::Get().GetTexture("circle")->ID);

        ball->SetColor(Color(gen(rng), gen(rng), gen(rng), 200));
        ball->SetVelocity(glm::vec2(0.05f * fgen(rng), 0.05f * fgen(rng)));
        mRenderer.Add(ball->GetRenderable());
        mEntities.push_back((Entity*)ball);
    }

    // Player
    mPlayer = new Player(300, 300, 32, 32, TextureManager::Get().GetTexture("hero")->ID);
    mPlayer->SetSpriteNumFrames(3, 4);
    mRenderer.Add(mPlayer->GetRenderable());
    mEntities.push_back(mPlayer);
}

void Game::CameraUpdate(float dt)
{
    float scaleSpeed = 1.0f + dt;

    if (Keyboard::Get().KeyDown(Keyboard::KEY_Q))
        mCamera.SetScale(mCamera.GetScale() * scaleSpeed);
    else if (Keyboard::Get().KeyDown(Keyboard::KEY_E))
        mCamera.SetScale(mCamera.GetScale() / scaleSpeed);

    // Follow the player
    mCamera.SetPos(
        mPlayer->GetPos().x + mPlayer->GetWidth() / 2,
        mPlayer->GetPos().y + mPlayer->GetHeight() / 2);

    // Send camera matrix to opengl
    mCamera.SetMatrix(shader->ID, "MVP");
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

#endif