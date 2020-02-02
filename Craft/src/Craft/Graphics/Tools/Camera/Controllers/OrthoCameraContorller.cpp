#include "crpch.h"

#include "OrthoCameraContorller.h"
#include <Craft/Core/InputHandler.h>

namespace Craft 
{
	OrthoCameraController::OrthoCameraController(f32 aspectRation, f32 sensivity) :
		m_AspectRation(aspectRation),
		CameraController(
			sensivity, 
			Camera::CreateOrthographicCamera(
				-m_AspectRation * m_ZoomLevel, 
				m_AspectRation * m_ZoomLevel, 
				-m_ZoomLevel, 
				m_ZoomLevel
			)
		)
	{
	}
	
	void OrthoCameraController::OnUpdate(f32 dt)
	{
		if (Input::InputHandler::IsKeyPressed('W'))
		{
			m_CemeraPos.y -= m_Sensitivity * dt;
		}
		if (Input::InputHandler::IsKeyPressed('S'))
		{
			m_CemeraPos.y += m_Sensitivity * dt;
		}
		if (Craft::Input::InputHandler::IsKeyPressed('A'))
		{
			m_CemeraPos.x += m_Sensitivity * dt;
		}
		if (Craft::Input::InputHandler::IsKeyPressed('D'))
		{
			m_CemeraPos.x -= m_Sensitivity * dt;
		}

		m_Camera->SetPosition(m_CemeraPos);
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthoCameraController::OnResizeWindow));
		dispatcher.Dispatch<MouseScrollWheelEvent>(BIND_EVENT_FN(OrthoCameraController::OnMouseScrollEvent));
	}

	bool OrthoCameraController::OnResizeWindow(WindowResizeEvent& e)
	{
		m_AspectRation = (f32)e.GetWidth() / (f32)e.GetHeight();
		m_Camera->SetProjectionMatrix(mat4::Ortho(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f));
		return true;
	}

	bool OrthoCameraController::OnMouseScrollEvent(MouseScrollWheelEvent& e)
	{
		f32 dir = e.GetZDelta();
		m_ZoomLevel -= dir * 0.25f;
		m_ZoomLevel = max(m_ZoomLevel, 0.25f);
		m_Camera->SetProjectionMatrix(mat4::Ortho(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f));
		return true;
	}
}