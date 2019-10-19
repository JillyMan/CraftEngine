#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class FPSCamera : public Camera
	{
	private:
		v3 m_Up;
		v3 m_Target;

	public:
		FPSCamera(v3& P, mat4& projMatrix, v3& target = v3(0.0f, 0.0f, 0.0f), v3& up = v3(0.0f, 1.0f, 0.0f)) : 
			Camera(projMatrix, P),
			m_Target(target),
			m_Up(up)
		{
			RecalculateMatrix();
		}

	protected:
		virtual void RecalculateMatrix() override
		{
			m_ViewMatrix = mat4::LookAt(m_Position, m_Up, m_Target);
		}
	};
}