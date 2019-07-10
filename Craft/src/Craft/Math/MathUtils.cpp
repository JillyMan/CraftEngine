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
		return (1 - t) * v0 + t * v1;
	}
}