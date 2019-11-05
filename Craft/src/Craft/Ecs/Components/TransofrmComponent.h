#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Ecs/Ecs.h>

namespace Craft { namespace Ecs {

	struct TransoformComponent : BaseComponent
	{
		f32 angle;
		v3 rotateAxis;
		v3 pos;
		v3 scale;
	};

} }