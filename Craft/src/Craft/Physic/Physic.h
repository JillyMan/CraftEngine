#pragma once

#include "Craft/Math/Math.h"

namespace Craft { namespace Physic {

	enum class ShapeKind
	{
		ShapeAABB,
		ShapeCircle
	};

	struct AABB
	{
		v2 min;
		v2 max;
	};

	struct Circle
	{
		f32 radius;
		v2 pos;
	};

	struct RigidBody
	{
		f32 restitution;

		f32 mass;
		f32 invertMass;

		v2 pos;
		v2 vel;
		v2 force;

		AABB shape;
	};

	struct Manifold
	{
		f32 penetration;
		v2 normal;
		RigidBody* A;
		RigidBody* B;
	};

	void Init();
	void UpdatePhysics(f32 dt);
	void AddRigidBody(RigidBody* body);
	RigidBody* CreateRigidBody(f32 restitution, f32 mass, const v2& pos, AABB& shape, const v2& vel = v2());

	void AddGlobalForce(v2& force);
	void ApplyForce(RigidBody& rigidBody, v2& force, f32 dt);

	bool CollisionAABB(RigidBody& a, RigidBody& b, Manifold& result);
	void ResolveCollision(Manifold& manifold);
	void PositionCorrection(Manifold& manifold);

	bool CirclevsCicle(Circle& a, Circle& b);
} }