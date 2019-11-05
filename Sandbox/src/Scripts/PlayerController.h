#pragma once

#include "Craft/Math/Math.h"
#include "Craft/Physic/Physic.h"
#include <Craft\Core\InputHandler.h>

class BoxCollider2D
{
public:
	BoxCollider2D(Craft::v2 pos, Craft::v2 size)
	{
		this->min = pos;
		this->max = pos + size;
	}

	bool IsCollide(BoxCollider2D& other, f32 xOverlap, f32 yOverlap) 
	{
	}

public:
	Craft::v2 min;
	Craft::v2 max;
};

class PlayerController
{
private:
	BoxCollider2D* boxCollider;
	Craft::Physic::RigidBody2DComponent* m_RigidBody;

public:
	f32 Speed;

	PlayerController(Craft::Physic::RigidBody2DComponent* rigidBody, f32 speed) :
		m_RigidBody(rigidBody), 
		Speed(speed)
	{
	}

public:
	void Update(f32 dt) 
	{
		Craft::v2 force;
		if (Craft::Input::InputHandler::IsKeyPressed(VK_UP))
		{
			force.y = 1.0f;
		}
		else if (Craft::Input::InputHandler::IsKeyPressed(VK_DOWN))
		{
			force.y = -1.0f;
		}

		if (Craft::Input::InputHandler::IsKeyPressed(VK_RIGHT))
		{
			force.x = 1.0f;
		}
		else if (Craft::Input::InputHandler::IsKeyPressed(VK_LEFT))
		{
			force.x = -1.0f;
		}

		m_RigidBody->vel = Lerp(
			Craft::v2(),
			m_RigidBody->vel + force,
			Craft::Claim01(dt * Speed));

		//Craft::Physic::ApplyForce(*m_RigidBody, force, dt / 100.0f);
	}

	Craft::v2& GetPosition() { return m_RigidBody->pos; }
};