#pragma once

#include "Craft/Math/Math.h"
#include <Craft/Physic/Components/RigidBody2DComponent.h>
#include <Craft/Physic/Components/BoxCollider2DComponent.h>

namespace Craft { namespace Physic {

	enum class ShapeKind
	{
		ShapeAABB,
		ShapeCircle
	};

	struct Circle
	{
		f32 radius;
		v2 pos;
	};
 
	void Init();
	void UpdatePhysics(f32 dt);
	void AddRigidBody(RigidBody2DComponent* body);
	RigidBody2DComponent* CreateRigidBody(f32 restitution, f32 mass, const v2& pos, BoxCollider2DComponent& shape, const v2& vel = v2());

	void AddGlobalForce(v2& force);
	void ApplyForce(RigidBody2DComponent& rigidBody, v2& force, f32 dt);
} }