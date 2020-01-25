#pragma once

#include "PerspectiveCamera.h"
#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Cameras/Camera.h>

namespace Craft
{
	class FPSCameraController
	{
	private:
		v3 m_Up;
		v3 m_Front;

		f32 m_Yaw;
		f32 m_Pitch;

		s32 m_LastX;
		s32 m_LastY;
		f32 m_Sensitivity;

		f32 m_CameraSpeed;

	private:
		Camera* m_Camera;

	public:
		FPSCameraController(
			f32 cameraSpeed, 
			v3& pos, 
			v3& front, 
			v3& up, 
			v2& camLastPos
		) :
			m_CameraSpeed(cameraSpeed),
			m_Front(front),
			m_Up(up),
			m_Pitch(0.0f),
			m_Yaw(-90.0f),
			m_Sensitivity(0.1f)
		{
			m_Camera = Camera::CreatePerspectiveCamera(75.0f, 16/9, 0.3f, 100.0f, pos, cameraSpeed);

			Input::InputHandler::GetMousePosition(m_LastX, m_LastY);

			RecalculateViewMatrix();
		}

		void OnMouseEvent(s32 xPos, s32 yPos)
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

		void SetLastPos(s32 x, s32 y) {
			m_LastX = x;
			m_LastY = y;
		}

		void Update(f32 dt)
		{
			v3 Pos = m_Camera->GetPosition();

			if (Input::InputHandler::IsKeyPressed('W')) {
				Pos -= m_Front * m_CameraSpeed * dt;
			}
			if (Input::InputHandler::IsKeyPressed('S')) {
				Pos += m_Front * m_CameraSpeed * dt;
			}
			if (Input::InputHandler::IsKeyPressed('A')) {
				Pos += Normalize(Cross(m_Front, m_Up)) * m_CameraSpeed * dt;
			}
			if (Input::InputHandler::IsKeyPressed('D')) {
				Pos -= Normalize(Cross(m_Front, m_Up))* m_CameraSpeed* dt;;
			}

			m_Camera->SetPosition(Pos);
			RecalculateViewMatrix();
		}

		Camera* GetCamera() { return m_Camera; }

	protected:
		void RecalculateViewMatrix()
		{
			v3 D;
			f32 PitchInRadians = ToRadians(m_Pitch);
			f32 YawInRadians = ToRadians(m_Yaw);
			D.x = cosf(PitchInRadians) * cosf(YawInRadians);
			D.y = sinf(PitchInRadians);
			D.z = cosf(PitchInRadians) * sinf(YawInRadians);

			m_Front = Normalize(D);
			v3 Pos = m_Camera->GetPosition();

			m_Camera->SetView(mat4::LookAt(Pos, Pos - m_Front, m_Up));
		}
	};
}