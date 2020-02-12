#pragma once

#include "Vectors.h"

namespace Craft
{
#define PI 3.1415926f
#define TWO_PI PI * 2
#define CERCLE_HALF_ANGLE 180.0f

	struct Rectangle {
		union {
			struct {
				f32 X, Y;
				f32 W, H;
			};
			v2 Pos;
			v2 Size;
		};
	};

	f32 ToRadians(f32 angle);
	f32 ToAngle(f32 radian);

	f32 Lerp(f32 v0, f32 v1, f32 t);
	f32 Claim01(f32 x);
}