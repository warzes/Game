#include "stdafx.h"
#if EXAMPLE_BREAKOUT
#include "GameObject.h"

namespace Breakout
{

	GameObject::GameObject()
		: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), SpriteTex(), IsSolid(false), Destroyed(false) { }

	GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
		: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), SpriteTex(sprite), IsSolid(false), Destroyed(false) { }

	void GameObject::Draw(SpriteRenderer& renderer)
	{
		renderer.DrawSprite(SpriteTex, this->Position, this->Size, this->Rotation, this->Color);
	}

}

#endif