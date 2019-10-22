#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far,
			v3& position, f32 cameraSpeed);

		virtual void MouseMove(s32 xPos, s32 yPos) override
		{
		}
	};
}