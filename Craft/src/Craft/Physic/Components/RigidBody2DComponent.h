#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Ecs/Ecs.h>

namespace Craft { namespace Physic {

	struct RigidBody2DComponent : BaseComponent
	{
		f32 mass;
		f32 invertMass;
		f32 restitution;

		v2 vel;

		void ApplyForce(v2 force) 
		{
			vel += force;
		}
	};

}}