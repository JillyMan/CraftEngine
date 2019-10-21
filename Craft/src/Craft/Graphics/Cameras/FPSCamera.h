#pragma once

#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class FPSCamera : public Camera
	{
	private:
		v3 m_Up;
		v3 m_Front;

		f32 m_Yaw;
		f32 m_Pitch;

		f32 m_LastX;
		f32 m_LastY;
		f32 m_Sensitivity;

	public:
		FPSCamera(f32 cameraSpeed, v3& P, v3& front, v3& up, v2 camLastPos, mat4& projMatrix) :
			Camera(projMatrix, P, cameraSpeed),
			m_Front(front),
			m_Up(up),
			m_Pitch(0.0f),
			m_Yaw(-90.0f),
			m_Sensitivity(0.1f),
			m_LastX(camLastPos.x),
			m_LastY(camLastPos.y)
		{
			RecalculateViewMatrix();
		}

		virtual void MouseMove(s32 xPos, s32 yPos) override
		{
			s32 xOffset = (xPos - m_LastX);
			s32 yOffset = (m_LastY - yPos);

			m_LastX = xPos;
			m_LastY = yPos;

			m_Yaw += (xOffset * m_Sensitivity);
			m_Pitch += (yOffset * m_Sensitivity);

			if (m_Pitch > 89.0f)
			{
				m_Pitch = 89.0f;
			}
			if (m_Pitch < -89.0f)
			{
				m_Pitch = -89.0f;
			}

			RecalculateViewMatrix();
		}

		virtual void Move(MoveDirection dir, f32 dt) override 
		{
			if (dir == MoveDirection::Up) {
				m_Position += m_Front * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Down) {
				m_Position -= m_Front * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Right) {
				m_Position += Normalize(Cross(m_Front, m_Up)) * m_CameraSpeed * dt;
			}
			if (dir == MoveDirection::Left) {
				m_Position -= Normalize(Cross(m_Front, m_Up))* m_CameraSpeed* dt;;
			}
			RecalculateViewMatrix();
		}

	protected:
		virtual void RecalculateViewMatrix() override
		{
			v3 D;
			D.x = cosf(ToRadians(m_Pitch)) * cosf(ToRadians(m_Yaw));
			D.y = sinf(ToRadians(m_Pitch));
			D.z = cosf(ToRadians(m_Pitch)) * sinf(ToRadians(m_Yaw));

			m_Front = Normalize(D);

			m_ViewMatrix = mat4::LookAt(m_Position, m_Position - m_Front, m_Up);
		}
	};
}