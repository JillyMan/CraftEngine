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

	void OrthographicCamera::RecalculateMatrix()
	{
		mat4 transform = mat4::Translate(m_Position) * mat4::Rotate(m_Rotation, v3 { 0.0f, 0.0f, 1.0f });
		m_ViewProjectionMatrix = m_ProjectionMatrix * transform;
	}
}