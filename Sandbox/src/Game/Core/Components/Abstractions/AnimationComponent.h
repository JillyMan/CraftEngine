#pragma once

#include "../GameObject.h"
#include <Craft.h>

class IAnimationComponent {
public:
	virtual ~IAnimationComponent() { }
	virtual void Animate(GameObject& obj, f32 dt) = 0;
};