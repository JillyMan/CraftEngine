#pragma once

#include <Craft.h>

class Transform2D {
public:
	Transform2D() {}

	Craft::mat4 ToModelMatrix() { return Craft::mat4::ModelMatrix(Pos, Scale, Rotation, Craft::v3(0.0f, 0.0f, 1.0f)); }

	inline void SetPos(Craft::v3 pos) { Pos = pos; }
	inline void SetScale(Craft::v3 scale) { Scale = Scale; }
	inline void SetRotation(f32 rot) { Rotation = rot; }

	f32 Rotation = 0.0f;
	Craft::v3 Pos;
	Craft::v3 Scale;
};