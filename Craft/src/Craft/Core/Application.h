#pragma once

#include "Core.h"
#include "Craft/Core/LayerStack.h"

#include "Craft/ImGui/ImGuiLayer.h"
#include "Craft/Window/Window.h"

#include "Craft/Event/Event.h"
#include "Craft/Event/KeyEvent.h"
#include "Craft/Event/ApplicationEvent.h"

namespace Craft {

	class CRAFT_API Application
	{
	private:
		u32 m_FPS;
		f32 m_LastTime;
		bool m_Running;

		Window* m_MainWindow;
		WindowSetting m_WindowSetting;

		ImGuiLayer* m_ImguiLayer;
		LayerStack m_layerStack;

	public:
		Application(WindowSetting& setting = WindowSetting());
		virtual ~Application();

		void Run();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_MainWindow; }

		f32 GetElapsedTime() { return m_LastTime; }
		f32 GetFps() { return m_FPS; }

	private:

		static Application* s_Instance;

		void OnRender();
		void OnUpdate(f32 deltaTime);
		void OnEvent(Event& event);

		bool OnKeyEvent(KeyPressedEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}