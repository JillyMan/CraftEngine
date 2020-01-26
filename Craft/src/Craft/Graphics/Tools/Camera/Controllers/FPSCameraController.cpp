#include "crpch.h"

#include "FPSCameraController.h"

namespace Craft {
	FPSCameraController::FPSCameraController(
		f32 speed,
		f32 sensivity,
		v3& pos,
		v3& front,
		v3& up,
		v2& camLastPos
	) :
		CameraController(
			sensivity,
			Camera::CreatePerspectiveCamera(75.0f, 16 / 9, 0.3f, 100.0f, pos)
		),
		m_Up(up),
		m_Front(front),
		m_Pitch(0.0f),
		m_Yaw(-90.0f),
		m_Speed(speed)
	{
		Input::InputHandler::GetMousePosition(m_LastX, m_LastY);
		RecalculateViewMatrix();
	}

	void FPSCameraController::OnEvent(Event& event) {
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::KeyReleasedEvent>(BIND_EVENT_FN(FPSCameraController::OnKeyReleased));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(FPSCameraController::OnKeyPressed));
		dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(FPSCameraController::OnMouseMoved));
	}

	void FPSCameraController::OnUpdate(f32 dt) {
		v3 Pos = m_Camera->GetPosition();

		if (Input::InputHandler::IsKeyPressed('W')) {
			Pos -= m_Front * m_Speed * dt;
		}
		if (Input::InputHandler::IsKeyPressed('S')) {
			Pos += m_Front * m_Speed * dt;
		}
		if (Input::InputHandler::IsKeyPressed('A')) {
			Pos += Normalize(Cross(m_Front, m_Up)) * m_Speed * dt;
		}
		if (Input::InputHandler::IsKeyPressed('D')) {
			Pos -= Normalize(Cross(m_Front, m_Up)) * m_Speed * dt;;
		}

		m_Camera->SetPosition(Pos);
		RecalculateViewMatrix();
	}

	void FPSCameraController::RecalculateViewMatrix()
	{
		v3 D;
		f32 PitchInRadians = ToRadians(m_Pitch);
		f32 YawInRadians = ToRadians(m_Yaw);
		D.x = cosf(PitchInRadians) * cosf(YawInRadians);
		D.y = sinf(PitchInRadians);
		D.z = cosf(PitchInRadians) * sinf(YawInRadians);

		m_Front = Normalize(D);
		v3 Pos = m_Camera->GetPosition();

		m_Camera->SetViewMatrix(mat4::LookAt(Pos, Pos - m_Front, m_Up));
	}

	bool FPSCameraController::OnMouseMoved(MouseMovedEvent& event) {
		//TODO: InputHandler that is just moke, will be deleted.

		if (m_IsDragged) {
			s32 xOffset = (event.x - m_LastX);
			s32 yOffset = (m_LastY - event.y);

			m_LastX = event.x;
			m_LastY = event.y;

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
			return true;
		}

		return false;
	}

	bool FPSCameraController::OnKeyPressed(KeyPressedEvent& event) {
		if (event.GetKeyCode() == 'R') {
			Input::InputHandler::GetMousePosition(m_LastX, m_LastY);
			m_IsDragged = true;
		}
		return m_IsDragged;
	}

	bool FPSCameraController::OnKeyReleased(KeyReleasedEvent& event) {
		if (event.GetKeyCode() == 'R') {
			m_IsDragged = false;
		}
		return !m_IsDragged;
	}
}