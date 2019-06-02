#pragma once

#include "crpch.h"

#include "Core.h"
#include "Event\Event.h"
#include "Craft\Graphics\Layer.h"
#include "Craft\Graphics\Window\Window.h"
#include "Event\ApplicationEvent.h"

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
//		void PopLayer(Layer* layer);

	private:
		void OnRender();
		void OnUpdate(f32 deltaTime);
		void OnEvent(Event& event);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}