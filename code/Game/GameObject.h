#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	// object state
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	float       Rotation;
	bool        IsSolid;
	bool        Destroyed;
	// render state
	Texture2D   SpriteTex;
	// constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// draw sprite
	virtual void Draw(SpriteRenderer& renderer);
};