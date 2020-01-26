#pragma once

#include "CameraController.h"
#include <Craft/Event/KeyEvent.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Tools/Camera/PerspectiveCamera.h>

namespace Craft
{
	//TODO: Now this is using like debug fps camera.
	class FPSCameraController : public CameraController
	{
	private:
		v3 m_Up;
		v3 m_Front;

		f32 m_Yaw;
		f32 m_Pitch;

		s32 m_LastX;
		s32 m_LastY;

		f32 m_Speed;
	private:
		bool m_IsDragged = false;

	public:
		FPSCameraController(
			f32 cameraSpeed,
			f32 sensivity,
			v3& pos,
			v3& front,
			v3& up,
			v2& camLastPos
		);

		virtual void OnEvent(Event& event) override;
		virtual void OnUpdate(f32 dt) override;

	private:
		void RecalculateViewMatrix();

		bool OnMouseMoved(MouseMovedEvent& event);

		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);

	};
}