#pragma once

#include <Craft/Math/Vectors.h>

struct LigthSource {
	f32 Ambient;
	Craft::v3 Dir;
	Craft::v3 Color;

	LigthSource() = default;

	LigthSource(
		f32 ambient, 
		Craft::v3& color
	) : 
		Ambient(ambient),
		Color(color)
	{
	}
};