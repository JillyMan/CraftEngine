#include "crpch.h"
#include "OrthographicCamera.h"

namespace Craft 
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top) :
		Camera(mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
	
	}

	void OrthographicCamera::SetProjection(f32 left, f32 right, f32 bottom, f32 top)
	{
		m_ProjectionMatrix = mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
}