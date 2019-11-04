#include "crpch.h"

#include "Craft\Core\Application.h"
#include "Utils\Timer.h"

#include "Craft\Window\WindowManager.h"

namespace Craft
{
	Application* Application::s_Instance = nullptr;

	Application::Application(WindowSetting& setting) :
		m_Running(false),
		m_FPS(setting.Fps)
	{
		CR_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_WindowSetting = setting;
		m_MainWindow = WindowManager::Create(setting);
		m_MainWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	
		m_ImguiLayer = new ImGuiLayer();
		PushOverlay(m_ImguiLayer);
	}

	Application::~Application()
	{
		WindowManager::Destroy(m_MainWindow);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_layerStack.PopOverlay(layer);
	}

	void Application::Run()
	{
		m_Running = true;

		Timer timer;
		m_LastTime = timer.ElapsedMillisecond();
		f32 resetInterval = timer.ElapsedMillisecond();
		f32 updateTick = 1000.0f / m_FPS;
		f32 delta = 0.0f;
		s32 frames = 0;
		s32 updates = 0;

		while (m_Running)
		{
			f32 nowTime = timer.ElapsedMillisecond();
			delta += nowTime - m_LastTime;
			m_LastTime = nowTime;

			if (delta > updateTick)
			{
				OnUpdate(delta/1000.0f);
				delta = 0.0f;
				++updates;

				++frames;
				OnRender();
				m_MainWindow->Update();
			}

			if (timer.ElapsedMillisecond() - resetInterval > 1000.0f)
			{
#ifdef CR_DEBUG
				String debug = m_WindowSetting.Title + " : FPS: " + std::to_string(frames) + \
					" Updates: " + std::to_string(updates) + " \n";
				m_MainWindow->SetTitle(debug);
#endif
				resetInterval += 1000.0f;
				frames = updates = 0;
			}
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyEvent));
		
		for (auto layer = m_layerStack.begin();
			layer != m_layerStack.end();
			++layer)
		{
			(*layer)->OnEvent(event);
		}
	}

	void Application::OnUpdate(f32 deltaTime)
	{
		for (auto layer = m_layerStack.begin();
			layer != m_layerStack.end();
			++layer)
		{
			(*layer)->OnUpdate(deltaTime);
		}
	}

	void Application::OnRender()
	{
		m_ImguiLayer->Begin();
		
		for (auto layer = m_layerStack.begin();
			layer != m_layerStack.end();
			++layer)
		{
			(*layer)->OnRender();
			(*layer)->OnDebugRender();
		}

		m_ImguiLayer->End();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		CR_INFO(e.ToString());
		m_Running = false;
		return true;
	}
	
	bool Application::OnKeyEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == VK_F1)
		{
			m_MainWindow->ToogleFullScreenMode();
		}

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return true;
	}
}