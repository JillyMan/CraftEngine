#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class FPSCamera : public Camera
	{
	private:
		v3 CamZ;
		v3 CamX;
		v3 CamY;

	public:
		FPSCamera(v3& P) : 
			Camera(mat4::Perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f), P)
		{
			RecalculateMatrix();
		}

	protected:
		virtual void RecalculateMatrix() override
		{
			CamZ = Normalize(m_Position);

			v3 up(0.0f, 1.0f, 0.0f);
			CamX = Normalize(Cross(up, CamZ));
			CamY = Normalize(Cross(CamX, CamZ));

			mat4 view = mat4::LookAt(CamX, CamY, CamZ) * mat4::Translate(-m_Position);
			m_ViewProjectionMatrix = m_ProjectionMatrix * view;
		}
	};
}