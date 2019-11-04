#include "MathUtils.h"

namespace Craft
{
	f32 ToRadians(f32 angle)
	{
		f32 result = angle * PI / CERCLE_HALF_ANGLE;
		return result;
	}

	f32 ToAngle(f32 radian)
	{
		f32 result = radian * CERCLE_HALF_ANGLE / PI;
		return result;
	}

	f32 Lerp(f32 v0, f32 v1, f32 t)
	{
		f32 tt = Claim01(t);
		return v0 + (v1 - v0) * tt;
	}

	f32 Claim01(f32 x) 
	{
		if (x > 1.0f) return 0.99f;
		else if (x < 0.0f) return 0.0f;
		return x;
	}
}