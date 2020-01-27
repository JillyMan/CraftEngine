#pragma once

#include "../GameObject.h"
#include <Craft.h>

class GraphicsComponent {
public:
	virtual ~GraphicsComponent() {}
	virtual void Draw(GameObject& obj) = 0;
};