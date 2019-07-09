#include "crpch.h"
#include "PerspectiveCamera.h"

namespace Craft
{
	PerspectiveCamera::PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far, v3& position)
		: Camera(mat4::Perspective(fov, aspectRatio, near, far), position)
	{
	}

	void PerspectiveCamera::RecalculateMatrix()
	{
		mat4 transform = mat4::Translate(m_Position) * mat4::Rotate(m_Rotation, v3{ 0.0f, 0.0f, 1.0f });
		m_ViewProjectionMatrix = m_ProjectionMatrix * transform;
	}
}