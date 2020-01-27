#pragma once

#include "../GameObject.h"
#include <Craft.h>

class AnimationComponent {
public:
	virtual ~AnimationComponent() { }
	virtual void Animate(GameObject& obj, f32 dt) = 0;
};