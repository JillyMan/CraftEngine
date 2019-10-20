#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position, f32 cameraSpeed = 0.0f);

		virtual void MouseMove(s32 xPos, s32 yPos) override
		{
		}
	};

}