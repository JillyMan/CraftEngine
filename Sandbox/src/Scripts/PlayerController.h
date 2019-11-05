#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Physic/Physic.h>
#include <Craft/Core/InputHandler.h>
#include <Craft/Physic/Components/BoxCollider2DComponent.h>
#include <Craft/Physic/Components/RigidBody2DComponent.h>
#include <Craft/Ecs/Components/TransofrmComponent.h>

class PlayerController
{
private:
	Craft::TransoformComponent* m_Transform;
	Craft::Physic::RigidBody2DComponent* m_RigidBody;

public:
	f32 Speed;

	PlayerController(
		Craft::Physic::RigidBody2DComponent* rigidBody,
		Craft::TransoformComponent* transform,
		f32 speed) :
		m_RigidBody(rigidBody),
		m_Transform(transform),
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
	}

	Craft::v2& GetPosition() { return m_Transform->pos.xy; }
};