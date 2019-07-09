#pragma once

#include "Camera.h"

namespace Craft
{
	class OrthographicCamera : public Camera
	{
	private:
		mat4 m_ProjectionMatrix;
		mat4 m_ViewMatrix;
		mat4 m_ViewProjectionMatrix;

		v3 m_Position;
		f32 m_Rotation = 0.0f;

	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, v3& position);

	protected:
		virtual void RecalculateMatrix() override;
	};
}