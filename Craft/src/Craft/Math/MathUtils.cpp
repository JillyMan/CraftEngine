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
}