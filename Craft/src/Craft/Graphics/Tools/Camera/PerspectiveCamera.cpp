#include "crpch.h"

#include <Craft/Graphics/Tools/Camera/Camera.h>
#include <Craft/Graphics/Tools/Camera/PerspectiveCamera.h>

namespace Craft
{
	PerspectiveCamera::PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position)
		: Camera(mat4::Perspective(fov, aspectRatio, near, far), position)
	{
	}
}