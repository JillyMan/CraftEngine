#pragma once

#include <Craft/Graphics/Tools/Camera/Camera.h>

namespace Craft
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near = -1.0f, f32 far = 1.0f);
	};
}