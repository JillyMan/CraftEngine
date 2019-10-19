#include "crpch.h"

#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Cameras/OrthographicCamera.h>
#include <Craft/Graphics/Cameras/PerspectiveCamera.h>

namespace Craft
{
	Camera::Camera(mat4& projectionMatrix, v3& position) :
		m_ProjectionMatrix(projectionMatrix),
		m_Position(position)
	{
	}

	Camera* Camera::CreatePerspectiveCamera(f32 fov, f32 aspectRatio, f32 _near, f32 _far, v3& position)
	{
		return new PerspectiveCamera(fov, aspectRatio, _near, _far, position);
	}

	Camera* Camera::CreateOrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, v3& position)
	{
		return new OrthographicCamera(left, right, bottom, top, position);
	}
}