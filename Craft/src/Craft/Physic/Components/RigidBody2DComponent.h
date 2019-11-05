#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Ecs/Ecs.h>

namespace Craft { namespace Physic {

	struct RigidBody2DComponent : Ecs::BaseComponent
	{
		f32 restitution;

		f32 mass;
		f32 invertMass;

		v2 vel;
		v2 force;
	};

}}