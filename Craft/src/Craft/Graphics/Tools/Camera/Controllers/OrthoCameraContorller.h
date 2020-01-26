#pragma once

#include "CameraController.h"

#include <Craft/Event/Event.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Event/ApplicationEvent.h>

#include <Craft/Graphics/Tools/Camera/OrthographicCamera.h>

namespace Craft 
{
	class OrthoCameraController : public CameraController
	{
	public:
		OrthoCameraController(f32 aspectRation, f32 sensivity = 5.0f);

		virtual void OnUpdate(f32 dt) override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnResizeWindow(WindowResizeEvent& e);
		bool OnMouseScrollEvent(MouseScrollWheelEvent& e);

		f32 m_AspectRation;
		v3 m_CemeraPos = { 0.0f, 0.0f, 0.0f };
	};

}