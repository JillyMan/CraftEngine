#pragma once

#include "Core.h"

#include "Craft\Layer.h"
#include "Craft\Window\Window.h"

#include "Craft\Event\Event.h"
#include "Craft\Event\KeyEvent.h"
#include "Craft\Event\ApplicationEvent.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Craft {

	class CRAFT_API Application
	{
	private:
		WindowSetting m_WindowSetting;
		Window* m_MainWindow;
		std::vector<Layer*> m_pLayers;
		bool m_Running;
		f32 m_FPS;

	public:
		Application(f32 fps = 60.0f);
		virtual ~Application();

		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

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