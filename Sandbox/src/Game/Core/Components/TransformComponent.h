#pragma once

#include <Craft/Math/Math.h>

struct Transform {
	Transform() = default;

	virtual Craft::mat4 ToModelMatrix() { return Craft::mat4::ModelMatrix(Pos, Scale, Rotation, Axis); }

	inline void SetPos(Craft::v3 pos) { Pos = pos; }
	inline void SetScale(Craft::v3 scale) { Scale = Scale; }
	inline void SetRotation(f32 rot, Craft::v3 axis = Craft::v3(0.0f, 0.0f, 1.0f)) { Rotation = rot; Axis = axis; }

	f32 Rotation = 0.0f;
	Craft::v3 Axis = Craft::v3(0.0f, 0.0f, 1.0f);
	Craft::v3 Pos = Craft::v3(0.0f, 0.0f, 0.0f);
	Craft::v3 Scale = Craft::v3(1.0f, 1.0f, 1.0f);
};
