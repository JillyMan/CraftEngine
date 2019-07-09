#include "crpch.h"
#include "OrthographicsCamera.h"

namespace Craft 
{
	OrthographicsCamera::OrthographicsCamera(f32 left, f32 right, f32 bottom, f32 top) :
		m_ProjectionMatrix(mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f)),
		m_ViewMatrix(mat4::Identity())
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicsCamera::RecalculateMatrix()
	{
		m_ViewMatrix = mat4::Translate(m_Position) * mat4::Rotate(m_Rotation, v3 { 0.0f, 0.0f, 1.0f });
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}