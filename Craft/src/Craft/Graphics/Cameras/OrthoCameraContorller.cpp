#include "crpch.h"

#include "Craft/Core/InputHandler.h"
#include "OrthoCameraContorller.h"

namespace Craft 
{
	OrthoCameraController::OrthoCameraController(f32 aspectRation) : 
		m_AspectRation(aspectRation), 
		m_Camera(-m_AspectRation* m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}
	
	void OrthoCameraController::Update(f32 dt)
	{
		if (Input::InputHandler::IsKeyPressed('W'))
		{
			m_CemeraPos.y -= m_CameraSpeed * dt;
		}
		if (Input::InputHandler::IsKeyPressed('S'))
		{
			m_CemeraPos.y += m_CameraSpeed * dt;
		}
		if (Craft::Input::InputHandler::IsKeyPressed('A'))
		{
			m_CemeraPos.x += m_CameraSpeed * dt;
		}
		if (Craft::Input::InputHandler::IsKeyPressed('D'))
		{
			m_CemeraPos.x -= m_CameraSpeed * dt;
		}

		m_Camera.SetPosition(m_CemeraPos);
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
		m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}

	bool OrthoCameraController::OnMouseScrollEvent(MouseScrollWheelEvent& e)
	{
		f32 dir = e.GetZDelta();
		dir = dir / abs(dir);
		m_ZoomLevel -= dir * 0.25f;
		m_ZoomLevel = max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}
}