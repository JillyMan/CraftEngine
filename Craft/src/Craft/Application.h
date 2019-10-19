#pragma once

#include "Core.h"

#include "Craft\Layer.h"
#include "Craft\Window\Window.h"

#include "Craft\Event\Event.h"
#include "Craft\Event\KeyEvent.h"
#include "Craft\Event\ApplicationEvent.h"

namespace Craft {

	class CRAFT_API Application
	{
	private:
		f32 m_FPS;
		f32 m_LastTime;
		bool m_Running;

		Window* m_MainWindow;
		WindowSetting m_WindowSetting;
		std::vector<Layer*> m_pLayers;

	public:
		Application(f32 fps = 60.0f, WindowSetting& setting = WindowSetting());
		virtual ~Application();

		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		f32 GetElapsedTime() { return m_LastTime; }

	private:
		void OnRender();
		void OnUpdate(f32 deltaTime);
		void OnEvent(Event& event);

		bool OnKeyEvent(KeyPressedEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}