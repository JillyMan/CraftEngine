#include "crpch.h"
#include "OrthographicCamera.h"

namespace Craft 
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far,
		v3& position, f32 cameraSpeed) :
		Camera(mat4::Ortho(left, right, bottom, top, near, far), position, cameraSpeed)
	{
	}
}