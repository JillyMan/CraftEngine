#include "crpch.h"
#include "Physic.h"

#include <Craft/Ecs/Components/TransofrmComponent.h>

namespace Craft { namespace Physic {

	template<typename T>
	using Container = std::vector<T>;
	using RigidBodyPair = std::pair<Craft::Physic::RigidBody2DComponent*, Craft::Physic::RigidBody2DComponent*>;

	struct Manifold
	{
		f32 penetration;
		v2 normal;
		RigidBody2DComponent* A;
		RigidBody2DComponent* B;
	};

	InternalVariable Container<RigidBodyPair> RigidBodyPairs;
	InternalVariable Container<Craft::Physic::RigidBody2DComponent*> Bodies;
	InternalVariable Container<Craft::v2> Forces;
	InternalVariable Container<Craft::Physic::BoxCollider2DComponent> Colliders;

	InternalFunction void ApplyVelocityForEachBody(Container<Craft::Physic::RigidBody2DComponent*> bodies, f32 dt);
	InternalFunction void ApplyGlobalForcesForEachBody(Container<Craft::Physic::RigidBody2DComponent*> bodies, f32 dt);
	InternalFunction bool CollisionAABB(RigidBody2DComponent& a, RigidBody2DComponent& b, Manifold& result);
	InternalFunction void ResolveCollision(Manifold& manifold);
	InternalFunction void PositionCorrection(Manifold& manifold);
	InternalFunction bool CirclevsCicle(Circle& a, Circle& b);
	InternalFunction void AddRigidBody(Craft::Physic::RigidBody2DComponent* body, Container<Craft::Physic::RigidBody2DComponent*>& bodies);

	void Craft::Physic::Init()
	{
		//todo: will add custom allocator.
	}

	void Craft::Physic::UpdatePhysics(f32 dt)
	{
		ApplyGlobalForcesForEachBody(Bodies, dt);
		ApplyVelocityForEachBody(Bodies, dt);

		for (RigidBodyPair& pair : RigidBodyPairs)
		{
			Manifold manifold;
			if (CollisionAABB(*pair.first, *pair.second, manifold))
			{
				ResolveCollision(manifold);
				PositionCorrection(manifold);
			}
		}
	}

	void Craft::Physic::AddGlobalForce(v2& force)
	{
		Forces.emplace_back(force);
	}

	Craft::Physic::RigidBody2DComponent* Craft::Physic::CreateRigidBody(f32 restitution, f32 mass, const v2& vel)
	{
		RigidBody2DComponent* body = new RigidBody2DComponent();
		CR_ASSERT(body, "Memory suck");

		body->mass = mass;
		body->invertMass = mass == 0 ? 0.0f : 1.0f / mass;
		body->restitution = restitution;
		body->vel = vel;

		Physic::AddRigidBody(body, Bodies);

		return body;
	}

	BoxCollider2DComponent* Craft::Physic::CreateBoxCollider2D(v2 min, v2 max)
	{
		BoxCollider2DComponent* collider = new BoxCollider2DComponent();
		CR_ASSERT(collider, "Memory suck");
		collider->min = min;
		collider->max = max;
		return collider;
	}

	void AddRigidBody(Craft::Physic::RigidBody2DComponent* body, Container<Craft::Physic::RigidBody2DComponent*>& bodies)
	{
		bodies.push_back(body);

		for (int i = 0; i < bodies.size() - 1; ++i)
		{
			RigidBodyPair pair = { body, bodies[i] };
			RigidBodyPairs.emplace_back(pair);
		}
	}

	void ApplyGlobalForcesForEachBody(Container<Craft::Physic::RigidBody2DComponent*> bodies, f32 dt)
	{
		for (Craft::Physic::RigidBody2DComponent* body : bodies)
		{
			for (Craft::v2& force : Forces)
			{
				body->ApplyForce(force * dt);
			}
		}
	}

	void ApplyVelocityForEachBody(Container<Craft::Physic::RigidBody2DComponent*> bodies, f32 dt)
	{
		for (Craft::Physic::RigidBody2DComponent* body : bodies)
		{
			TransoformComponent& transform = *Ecs::Ecs::GetComponentById<TransoformComponent>(body->ownderId);
			transform.pos = Craft::Lerp(transform.pos, transform.pos + v3(body->vel, 0.0f), dt);
		}
	}

	inline bool GetOverlap(
		Craft::Physic::BoxCollider2DComponent& a, Craft::Physic::BoxCollider2DComponent& b,
		Craft::v2 fromAToB,
		f32& xOverlap, f32& yOverlap)
	{
		f32 a_x_half = (a.max.x - a.min.x) / 2.0f;
		f32 b_x_half = (b.max.x - b.min.x) / 2.0f;

		f32 a_y_half = (a.max.y - a.min.y) / 2.0f;
		f32 b_y_half = (b.max.y - b.min.y) / 2.0f;

		xOverlap = a_x_half + b_x_half - fabs(fromAToB.x);
		if (xOverlap > 0)
		{
			yOverlap = a_y_half + b_y_half - fabs(fromAToB.y);
			if (yOverlap > 0)
			{
				return true;
			}
		}

		return false;
	}

	bool CollisionAABB(RigidBody2DComponent& a, RigidBody2DComponent& b, Manifold& result)
	{
		bool isInterset = false;

		BoxCollider2DComponent& aBox = *Ecs::Ecs::GetComponentById<BoxCollider2DComponent>(a.ownderId);
		BoxCollider2DComponent& bBox = *Ecs::Ecs::GetComponentById<BoxCollider2DComponent>(b.ownderId);

		TransoformComponent& aTransform = *Ecs::Ecs::GetComponentById<TransoformComponent>(a.ownderId);
		TransoformComponent& bTransform = *Ecs::Ecs::GetComponentById<TransoformComponent>(b.ownderId);

		v3 fromAToB = bTransform.pos - aTransform.pos;

		f32 x_overlap, y_overlap;
		if (GetOverlap(aBox, bBox, v2(fromAToB.x, fromAToB.y), x_overlap, y_overlap))
		{
			if (x_overlap > y_overlap)
			{
				result.normal = fromAToB.y < 0.0f ? v2(0.0f, -1.0f) : v2(0.0f, 1.0f);
				result.penetration = x_overlap;
			}
			else
			{
				result.normal = fromAToB.x < 0.0f ? v2(-1.0f, 0.0f) : v2(1.0f, 0.0f);
				result.penetration = y_overlap;
			}
			result.A = &a;
			result.B = &b;

			isInterset = true;
		}

		return isInterset;
	}

	void ResolveCollision(Manifold& manifold)
	{
		RigidBody2DComponent& a = *manifold.A;
		RigidBody2DComponent& b = *manifold.B;
		Craft::v2& normal = manifold.normal;

		Craft::v2 velFromAToB = b.vel - a.vel;
		f32 velAlongNormal = Dot(velFromAToB, normal);

		if (velAlongNormal > 0)
			return;

		f32 e = min(a.restitution, b.restitution);

		f32 j = -(1 + e) * velAlongNormal;
		j /= (a.invertMass + b.invertMass);

		f32 mass_sum = a.mass + b.mass;
		f32 rationAMass = a.mass / mass_sum;
		f32 rationBMass = b.mass / mass_sum;

		Craft:v2 impulse = normal * j;
		a.vel -= impulse * rationAMass;
		b.vel += impulse * rationBMass;
	}

	void PositionCorrection(Manifold& manifold)
	{
		const f32 percentOfReduce = 0.5f;
		const f32 slop = 0.06;

		RigidBody2DComponent& a = *manifold.A;
		RigidBody2DComponent& b = *manifold.B;
		TransoformComponent& aTransform = *Ecs::Ecs::GetComponentById<TransoformComponent>(a.ownderId);
		TransoformComponent& bTransform = *Ecs::Ecs::GetComponentById<TransoformComponent>(b.ownderId);

		f32 mass_sum = a.invertMass + b.invertMass;
		f32 penetration = manifold.penetration;
		v2 collisionNormal = manifold.normal;
		v2 correction = collisionNormal * ((max(penetration - slop, 0.0f) / (mass_sum)) * percentOfReduce);
		
		//todo: usseles complexity to transform from v2() to v3()?? need fix.
		aTransform.pos -= v3(correction * a.invertMass, aTransform.pos.z);
		bTransform.pos += v3(correction * b.invertMass, aTransform.pos.z);
	}

	bool CirclevsCicle(Circle& a, Circle& b)
	{
		f32 distanceBetween = Craft::Length(a.pos - b.pos);
		f32 r = a.radius + b.radius;
		return r < distanceBetween;
	}
}}