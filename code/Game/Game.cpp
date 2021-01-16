#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Input.h"
#include "BallObject.h"

#define SIMPLE_SPRITE 0

SpriteRenderer* sprite;
GameObject* Player;
BallObject* Ball;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

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
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	ResourceManager::LoadShader("../data/shaders/sprite.vs", "../data/shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
#if SIMPLE_SPRITE
	ResourceManager::LoadTexture("../data/images/test.png", true, "face");
#else
	// load textures
	ResourceManager::LoadTexture("../data/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("../data/textures/ball.png", true, "face");
	ResourceManager::LoadTexture("../data/textures/block.png", false, "block");
	ResourceManager::LoadTexture("../data/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("../data/textures/paddle.png", true, "paddle");

	// load levels
	GameLevel one; one.Load("../data/levels/one.lvl", width, height / 2);
	GameLevel two; two.Load("../data/levels/two.lvl", width, height / 2);
	GameLevel three; three.Load("../data/levels/three.lvl", width, height / 2);
	GameLevel four; four.Load("../data/levels/four.lvl", width, height / 2);
	Levels.push_back(one);
	Levels.push_back(two);
	Levels.push_back(three);
	Levels.push_back(four);
	Level = 2;

	glm::vec2 playerPos = glm::vec2(
		width / 2.0f - PLAYER_SIZE.x / 2.0f,
		height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
		-BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
		ResourceManager::GetTexture("face"));
#endif
}

void Game::Update(float dt)
{
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	Ball->Move(dt, width);

	// check for collisions
	DoCollisions();
	// check loss condition
	if (Ball->Position.y >= height) // did ball reach bottom edge?
	{
		ResetLevel();
		ResetPlayer();
	}
}

void Game::ProcessInput(float dt)
{
	if (State == GameState::Active)
	{
		static auto& engineConfig = GetEngine().GetConfig();
		auto& width = engineConfig.window.width;
		auto& height = engineConfig.window.height;

		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (Keyboard::Get().KeyDown(Keyboard::KEY_A))
		{
			if (Player->Position.x >= 0.0f)
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
					Ball->Position.x -= velocity;
			}
		}
		if (Keyboard::Get().KeyDown(Keyboard::KEY_D))
		{
			if (Player->Position.x <= width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
					Ball->Position.x += velocity;
			}
		}
		if (Keyboard::Get().KeyDown(Keyboard::KEY_SPACE))
			Ball->Stuck = false;
	}
}

void Game::Render()
{
#if SIMPLE_SPRITE
	sprite->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
#else
	if (State == GameState::Active)
	{
		static auto& engineConfig = GetEngine().GetConfig();
		auto& width = engineConfig.window.width;
		auto& height = engineConfig.window.height;

		// draw background
		sprite->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height), 0.0f);
		// draw level
		this->Levels[this->Level].Draw(*sprite);
		Player->Draw(*sprite);
		Ball->Draw(*sprite);
	}
#endif
}

void Game::Close()
{
	delete sprite;
	delete Player;
	delete Ball;
	ResourceManager::Clear();
}

void Game::ResetLevel()
{
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	if (this->Level == 0)
		this->Levels[0].Load("../data/levels/one.lvl", width, height / 2);
	else if (this->Level == 1)
		this->Levels[1].Load("../data/levels/two.lvl", width, height / 2);
	else if (this->Level == 2)
		this->Levels[2].Load("../data/levels/three.lvl", width, height / 2);
	else if (this->Level == 3)
		this->Levels[3].Load("../data/levels/four.lvl", width, height / 2);
}

void Game::ResetPlayer()
{
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	// reset player/ball stats
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(width / 2.0f - PLAYER_SIZE.x / 2.0f, height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

// collision detection
bool CheckCollision(GameObject& one, GameObject& two);
Collision CheckCollision(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
	for (GameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // if collision is true
			{
				// destroy block if not solid
				if (!box.IsSolid)
					box.Destroyed = true;
				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // horizontal collision
				{
					Ball->Velocity.x = -Ball->Velocity.x; // reverse horizontal velocity
					// relocate
					float penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // move ball to right
					else
						Ball->Position.x -= penetration; // move ball to left;
				}
				else // vertical collision
				{
					Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
					// relocate
					float penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration; // move ball bback up
					else
						Ball->Position.y += penetration; // move ball back down
				}
			}
		}
	}
	// check collisions for player pad (unless stuck)
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		// check where it hit the board, and change velocity based on where it hit the board
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);
		// then move accordingly
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
		// fix sticky paddle
		Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
	}
}

bool CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
{
	// collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

Collision CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
{
	// get center point circle first 
	glm::vec2 center(one.Position + one.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;

	if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

// calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}