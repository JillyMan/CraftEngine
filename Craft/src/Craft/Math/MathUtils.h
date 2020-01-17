#pragma once

namespace Craft
{

#define PI 3.1415926f
#define TWO_PI PI * 2
#define CERCLE_HALF_ANGLE 180.0f

	f32 ToRadians(f32 angle);
	f32 ToAngle(f32 radian);

	f32 Lerp(f32 v0, f32 v1, f32 t);
	f32 Claim01(f32 x);
}