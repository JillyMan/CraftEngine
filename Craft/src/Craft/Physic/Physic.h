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

	RigidBody2DComponent* CreateRigidBody(f32 restitution, f32 mass, const v2& vel = v2());

	BoxCollider2DComponent* CreateBoxCollider2D(v2 min, v2 max);


	void AddGlobalForce(v2& force);
} }