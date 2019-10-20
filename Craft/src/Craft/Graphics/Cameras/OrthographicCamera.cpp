#include "crpch.h"
#include "OrthographicCamera.h"

namespace Craft 
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top,
		v3& position, f32 cameraSpeed) :
		Camera(mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f), position, cameraSpeed)
	{
	}
}