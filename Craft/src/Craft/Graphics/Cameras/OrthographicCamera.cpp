#include "crpch.h"
#include "OrthographicCamera.h"

namespace Craft 
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top,
		v3& position) :
		Camera(mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f), position)
	{
		RecalculateMatrix();
	}
}