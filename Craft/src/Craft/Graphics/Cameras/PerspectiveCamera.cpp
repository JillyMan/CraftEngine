#include "crpch.h"

#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Cameras/PerspectiveCamera.h>

namespace Craft
{
	PerspectiveCamera::PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position, f32 cameraSpeed)
		: Camera(mat4::Perspective(fov, aspectRatio, near, far), position, cameraSpeed)
	{
	}
}