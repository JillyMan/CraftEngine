#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Ecs/Ecs.h>

namespace Craft { namespace Physic {

	struct BoxCollider2DComponent : BaseComponent
	{
		v2 min;
		v2 max;
	};

} }