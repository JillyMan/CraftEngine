#include "crpch.h"

#include "OrthographicCamera.h"
#include <Craft/Math/Matrix.h>

namespace Craft 
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) :
		Camera(mat4::Ortho(left, right, bottom, top, near, far))
	{
	
	}
}