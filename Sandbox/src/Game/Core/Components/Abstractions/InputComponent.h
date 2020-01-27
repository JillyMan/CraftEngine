#pragma once

#include "../GameObject.h"
#include <Craft.h>

class InputComponent {
public:
	virtual ~InputComponent() {};
	virtual void Update(GameObject& obj, f32 dt) = 0;
};