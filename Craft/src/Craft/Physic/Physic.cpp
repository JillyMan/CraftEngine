#include "crpch.h"
#include "Physic.h"

#define START_CAPACITY 10

using RigidBodyPair = std::pair<Craft::Physic::RigidBody*, Craft::Physic::RigidBody*>;

template<typename T>
using Container = std::vector<T>;

InternalVariable Container<RigidBodyPair> RigidBodyPairs;
InternalVariable Container<Craft::Physic::RigidBody*> Bodies;
InternalVariable Container<Craft::v2> Forces;

void Craft::Physic::AddRigidBody(Craft::Physic::RigidBody* body)
{
	Bodies.push_back(body);

	for (int i = 0; i < Bodies.size() - 1; ++i) 
	{
		RigidBodyPair pair = { body, Bodies[i] };
		RigidBodyPairs.emplace_back(pair);
	}
}

void Craft::Physic::AddGlobalForce(v2& force)
{
	Forces.emplace_back(force);
}

void Craft::Physic::Init()
{
	//todo: will add custom allocator.
}

InternalFunction void ApplyGlobalForcesForEachBody(Container<Craft::Physic::RigidBody*> bodies, f32 dt) 
{
	for (Craft::Physic::RigidBody* body : bodies) 
	{
		for (Craft::v2& force : Forces) 
		{
			Craft::Physic::ApplyForce(*body, force, dt);
		}
	}
}

InternalFunction void ApplyVelocityForEachBody(Container<Craft::Physic::RigidBody*> bodies, f32 dt)
{
	for (Craft::Physic::RigidBody* body : bodies)
	{
		body->pos = Craft::Lerp(body->pos, body->pos + body->vel, dt);
	}
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

void Craft::Physic::ApplyForce(RigidBody& rigidBody, v2& force, f32 dt) 
{
	rigidBody.vel += force * dt;
}

Craft::Physic::RigidBody* Craft::Physic::CreateRigidBody(f32 restitution, f32 mass, const v2& pos, AABB& shape, const v2& vel)
{
	RigidBody* body = (RigidBody*)malloc(sizeof(RigidBody));
	if (body == nullptr)
	{ 
		return nullptr;
	}
	body->mass = mass;
	body->invertMass = mass == 0 ? 0.0f : 1.0f / mass;
	body->restitution = restitution;
	body->pos = pos;
	body->vel = vel;
	body->shape = shape;
	
	Physic::AddRigidBody(body);

	return body;
}

InternalFunction inline bool GetOverlap(
	Craft::Physic::AABB& a, Craft::Physic::AABB& b, 
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

bool Craft::Physic::CollisionAABB(RigidBody& a, RigidBody& b, Manifold& result)
{
	bool isInterset = false;
	AABB& abox = a.shape;
	AABB& bbox = b.shape;
	v2 fromAToB = b.pos - a.pos;

	f32 x_overlap, y_overlap;
	if (GetOverlap(abox, bbox, fromAToB, x_overlap, y_overlap)) 
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

void Craft::Physic::ResolveCollision(Manifold& manifold)
{
	RigidBody& a = *manifold.A;
	RigidBody& b = *manifold.B;
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

void Craft::Physic::PositionCorrection(Manifold& manifold)
{
	const f32 percentOfReduce = 0.5f;
	const f32 slop = 0.06;

	RigidBody& a = *manifold.A;
	RigidBody& b = *manifold.B;

	f32 mass_sum = a.invertMass + b.invertMass;
	f32 penetration = manifold.penetration;
	v2 collisionNormal = manifold.normal;
	v2 correction = collisionNormal * ((max(penetration - slop, 0.0f) / (mass_sum)) * percentOfReduce);

	a.pos -= correction * a.invertMass;
	b.pos += correction * b.invertMass;
}

bool Craft::Physic::CirclevsCicle(Circle& a, Circle& b)
{
	f32 distanceBetween = Craft::Length(a.pos - b.pos);
	f32 r = a.radius + b.radius;
	return r < distanceBetween;
}