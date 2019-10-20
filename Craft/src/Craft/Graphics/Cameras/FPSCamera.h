#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class FPSCamera : public Camera
	{
	private:
		v3 m_Up;
		v3 m_Front;

	public:
		FPSCamera(f32 cameraSpeed, v3& P, v3& front, v3& up, mat4& projMatrix) :
			Camera(projMatrix, P, cameraSpeed),
			m_Front(front),
			m_Up(up)
		{
		}

		virtual void Move(MoveDirection dir, f32 dt) override 
		{
			if (dir == MoveDirection::Up) {
				m_Position -= m_Front * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Down) {
				m_Position += m_Front * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Right) {
				m_Position -= Normalize(Cross(m_Front, m_Up)) * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Left) {
				m_Position += Normalize(Cross(m_Front, m_Up))* m_CameraSpeed* dt;;
			}
			RecalculateViewMatrix();
		}

	protected:
		virtual void RecalculateViewMatrix() override
		{
			m_ViewMatrix = mat4::LookAt(m_Position, m_Position - m_Front, m_Up);
		}
	};
}