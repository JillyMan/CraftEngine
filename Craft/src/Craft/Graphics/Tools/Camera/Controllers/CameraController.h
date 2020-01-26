#pragma once

#include <Craft/Core/Layer.h>
#include <Craft/Graphics/Tools/Camera/Camera.h>

namespace Craft {

	class CameraController : public EventListener, public UpdateListener {
	protected:
		Camera* m_Camera;
		f32 m_Sensitivity;
		f32 m_ZoomLevel = 1.0f;

	public:
		CameraController(f32 sensivity, Camera* camera) : 
			m_Camera(camera),
			m_Sensitivity(sensivity)
		{}

		virtual ~CameraController() {
			if (m_Camera) {
				delete m_Camera;
			}
		}

		f32 GetSensivity() const { return m_Sensitivity; }
		void SetSensivity(f32 sensivity) { m_Sensitivity = sensivity; }

		f32 GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(f32 level) { m_ZoomLevel = level; }

		Camera* GetCamera() const { return m_Camera; }

		virtual void OnUpdate(f32 dt) override = 0;
		virtual void OnEvent(Event& event) override = 0;
	};

}