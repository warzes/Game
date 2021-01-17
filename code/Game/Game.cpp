#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Input.h"
#include "BallObject.h"
#include "Particle.h"
#include "PostProcessor.h"
#include "TextRenderer.h"

using namespace irrklang;

#define SIMPLE_SPRITE 0

SpriteRenderer* sprite;
GameObject* Player;
BallObject* Ball;
ParticleGenerator* Particles;
PostProcessor* Effects;
TextRenderer* Text;

ISoundEngine* SoundEngine = createIrrKlangDevice();

float ShakeTime = 0.0f;

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

	// load shaders
	ResourceManager::LoadShader("../data/shaders/sprite.vs", "../data/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("../data/shaders/particle.vs", "../data/shaders/particle.frag", nullptr, "particle");
	ResourceManager::LoadShader("../data/shaders/post_processing.vs", "../data/shaders/post_processing.frag", nullptr, "postprocessing");

	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

	// load textures
	ResourceManager::LoadTexture("../data/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("../data/textures/ball.png", true, "face");
	ResourceManager::LoadTexture("../data/textures/block.png", false, "block");
	ResourceManager::LoadTexture("../data/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("../data/textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("../data/textures/particle.png", true, "particle");
	ResourceManager::LoadTexture("../data/textures/powerup_speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("../data/textures/powerup_sticky.png", true, "powerup_sticky");
	ResourceManager::LoadTexture("../data/textures/powerup_increase.png", true, "powerup_increase");
	ResourceManager::LoadTexture("../data/textures/powerup_confuse.png", true, "powerup_confuse");
	ResourceManager::LoadTexture("../data/textures/powerup_chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("../data/textures/powerup_passthrough.png", true, "powerup_passthrough");
#if SIMPLE_SPRITE
	ResourceManager::LoadTexture("../data/images/test.png", true, "face");
#else

	// set render-specific controls
	sprite = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 2000);
	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), width, height);

	// load levels
	GameLevel one; one.Load("../data/levels/one.lvl", width, height / 2);
	GameLevel two; two.Load("../data/levels/two.lvl", width, height / 2);
	GameLevel three; three.Load("../data/levels/three.lvl", width, height / 2);
	GameLevel four; four.Load("../data/levels/four.lvl", width, height / 2);
	Levels.push_back(one);
	Levels.push_back(two);
	Levels.push_back(three);
	Levels.push_back(four);
	Level = 0;

	// configure game objects
	glm::vec2 playerPos = glm::vec2(width / 2.0f - PLAYER_SIZE.x / 2.0f, height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));

	SoundEngine->play2D("../data/audio/breakout.mp3", true);

	Text = new TextRenderer(width, height);
	Text->Load("../data/fonts/ocraext.TTF", 24);
#endif
}

void Game::Update(float dt)
{
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	// update objects
	Ball->Move(dt, width);
	// check for collisions
	DoCollisions();
	// update particles
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
	// update PowerUps
	UpdatePowerUps(dt);
	// reduce shake time
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			Effects->Shake = false;
	}
	// check loss condition
	if (Ball->Position.y >= height) // did ball reach bottom edge?
	{
		--this->Lives;
		// did the player lose all his lives? : Game over
		if (this->Lives == 0)
		{
			ResetLevel();
			State = GameState::Menu;
		}
		ResetPlayer();
	}
	// check win condition
	if (this->State == GameState::Active && this->Levels[this->Level].IsCompleted())
	{
		this->ResetLevel();
		this->ResetPlayer();
		Effects->Chaos = true;
		this->State = GameState::Win;
	}
}

void Game::ProcessInput(float dt)
{
	if (this->State == GameState::Menu)
	{
		if (Keyboard::Get().KeyPressed(Keyboard::KEY_ENTER))
		{
			this->State = GameState::Active;
		}
		if (Keyboard::Get().KeyPressed(Keyboard::KEY_W))
		{
			this->Level = (this->Level + 1) % 4;
		}
		if (Keyboard::Get().KeyPressed(Keyboard::KEY_S))
		{
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
		}
	}
	if (this->State == GameState::Win)
	{
		if (Keyboard::Get().KeyPressed(Keyboard::KEY_ENTER))
		{
			Effects->Chaos = false;
			this->State = GameState::Menu;
		}
	}
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
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

#if SIMPLE_SPRITE
	sprite->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
#else
	if (State == GameState::Active || this->State == GameState::Menu || this->State == GameState::Win)
	{
		// begin rendering to postprocessing framebuffer
		Effects->BeginRender();
		{
			// draw background
			sprite->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height), 0.0f);
			// draw level
			this->Levels[this->Level].Draw(*sprite);
			// draw player
			Player->Draw(*sprite);
			// draw PowerUps
			for (PowerUp& powerUp : this->PowerUps)
				if (!powerUp.Destroyed)
					powerUp.Draw(*sprite);
			// draw particles	
			Particles->Draw();
			// draw ball
			Ball->Draw(*sprite);
		}

		// end rendering to postprocessing framebuffer
		Effects->EndRender();
		// render postprocessing quad
		static float time = 0.0f;
		time += 0.001f;
		Effects->Render(time);// TODO: GetTime

		std::stringstream ss; ss << Lives;
		Text->RenderText("Lives:" + ss.str(), 5.0f, 5.0f, 1.0f);
	}
	if (this->State == GameState::Menu)
	{
		Text->RenderText("Press ENTER to start", 250.0f, height / 2.0f, 1.0f);
		Text->RenderText("Press W or S to select level", 245.0f, height / 2.0f + 20.0f, 0.75f);
	}
	if (this->State == GameState::Win)
	{
		Text->RenderText("You WON!!!", 320.0f, height / 2.0f - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, height / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	}
#endif
}

void Game::Close()
{
	delete sprite;
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
	delete Text;
	SoundEngine->drop();
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

	Lives = 3;
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
	// also disable all active powerups
	Effects->Chaos = Effects->Confuse = false;
	Ball->PassThrough = Ball->Sticky = false;
	Player->Color = glm::vec3(1.0f);
	Ball->Color = glm::vec3(1.0f);
}

// powerups
bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);

void Game::UpdatePowerUps(float dt)
{
	for (PowerUp& powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				// remove powerup from list (will later be removed)
				powerUp.Activated = false;
				// deactivate effects
				if (powerUp.Type == "sticky")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{	// only reset if no other PowerUp of type sticky is active
						Ball->Sticky = false;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
					{	// only reset if no other PowerUp of type pass-through is active
						Ball->PassThrough = false;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
					{	// only reset if no other PowerUp of type confuse is active
						Effects->Confuse = false;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{	// only reset if no other PowerUp of type chaos is active
						Effects->Chaos = false;
					}
				}
			}
		}
	}
	// Remove all PowerUps from vector that are destroyed AND !activated (thus either off the map or finished)
	// Note we use a lambda expression to remove each PowerUp which is destroyed and not activated
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp& powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
	), this->PowerUps.end());
}

bool ShouldSpawn(unsigned int chance)
{
	unsigned int random = rand() % chance;
	return random == 0;
}
void Game::SpawnPowerUps(GameObject& block)
{
	if (ShouldSpawn(75)) // 1 in 75 chance
		this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
	if (ShouldSpawn(15)) // Negative powerups should spawn more often
		this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
	if (ShouldSpawn(15))
		this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
}

void ActivatePowerUp(PowerUp& powerUp)
{
	if (powerUp.Type == "speed")
	{
		Ball->Velocity *= 1.2;
	}
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = true;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = true;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effects->Chaos)
			Effects->Confuse = true; // only activate if chaos wasn't already active
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effects->Confuse)
			Effects->Chaos = true;
	}
}

bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
	// Check if another PowerUp of the same type is still active
	// in which case we don't disable its effect (yet)
	for (const PowerUp& powerUp : powerUps)
	{
		if (powerUp.Activated)
			if (powerUp.Type == type)
				return true;
	}
	return false;
}

// collision detection
bool CheckCollision(GameObject& one, GameObject& two);
Collision CheckCollision(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
	static auto& engineConfig = GetEngine().GetConfig();
	auto& width = engineConfig.window.width;
	auto& height = engineConfig.window.height;

	for (GameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // if collision is true
			{
				// destroy block if not solid
				if (!box.IsSolid)
				{
					box.Destroyed = true;
					this->SpawnPowerUps(box);
					SoundEngine->play2D("../data/audio/bleep.mp3", false);
				}
				else
				{   // if block is solid, enable shake effect
					ShakeTime = 0.05f;
					Effects->Shake = true;
					SoundEngine->play2D("../data/audio/solid.wav", false);
				}
				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid)) // don't do collision resolution on non-solid bricks if pass-through is activated
				{
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
	}

	// also check collisions on PowerUps and if so, activate them
	for (PowerUp& powerUp : this->PowerUps)
	{
		if (!powerUp.Destroyed)
		{
			// first check if powerup passed bottom edge, if so: keep as inactive and destroy
			if (powerUp.Position.y >= height)
				powerUp.Destroyed = true;

			if (CheckCollision(*Player, powerUp))
			{	// collided with player, now activate powerup
				ActivatePowerUp(powerUp);
				powerUp.Destroyed = true;
				powerUp.Activated = true;
				SoundEngine->play2D("../data/audio/powerup.wav", false);
			}
		}
	}

	// and finally check collisions for player pad (unless stuck)
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

		// if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
		Ball->Stuck = Ball->Sticky;

		SoundEngine->play2D("../data/audio/bleep.wav", false);
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