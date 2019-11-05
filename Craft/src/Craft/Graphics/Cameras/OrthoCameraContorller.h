#pragma once

#include "Craft/Event/Event.h"
#include "Craft/Event/ApplicationEvent.h"
#include "Craft/Event/MouseEvent.h"

#include "OrthographicCamera.h"

namespace Craft 
{
	class OrthoCameraController
	{
	public:
		OrthoCameraController(f32 aspectRation);

		void Update(f32 dt);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }

		f32 GetCameraSpeed() { return m_CameraSpeed; }
		void SetCameraSpeed(f32 speed) { m_CameraSpeed = speed; }

		f32 GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(f32 level) { m_ZoomLevel = level; }

	private:
		bool OnResizeWindow(WindowResizeEvent& e);
		bool OnMouseScrollEvent(MouseScrollWheelEvent& e);

		f32 m_AspectRation;
		f32 m_ZoomLevel = 5.0f;
		f32 m_CameraSpeed = 5.0f;
		v3 m_CemeraPos = { 0.0f, 0.0f, 0.0f };
		OrthographicCamera m_Camera;
	};

}