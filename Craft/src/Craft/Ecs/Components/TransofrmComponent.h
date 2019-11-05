#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Ecs/Components/BaseComponents.h>

namespace Craft {

	struct TransoformComponent : BaseComponent
	{
		f32 angle;
		v3 rotateAxis;
		v3 pos;
		v3 scale;
	};

}