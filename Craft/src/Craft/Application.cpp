#include "crpch.h"

#include "Application.h"
#include "Utils\Timer.h"

#include "Craft\Window\WindowManager.h"

namespace Craft
{
	Application::Application(f32 fps) :
		m_Running(false),
		m_FPS(fps)
	{
		m_MainWindow = WindowManager::Create();
		m_MainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		WindowManager::Destroy(m_MainWindow);
		
		for (int i = 0; i < m_pLayers.size(); ++i)
		{
			delete m_pLayers[i];
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_pLayers.emplace_back(layer);
	}

	void Application::Run()
	{
		m_Running = true;

		Timer timer;
		f32 lastTime = timer.ElapsedMillisecond();
		f32 resetInterval = timer.ElapsedMillisecond();
		f32 updateTick = 1000.0f / m_FPS;
		f32 delta = 0.0f;
		s32 frames = 0;
		s32 updates = 0;

		while (m_Running)
		{
			f32 nowTime = timer.ElapsedMillisecond();
			delta += nowTime - lastTime;
			lastTime = nowTime;

			if (delta > updateTick)
			{
				OnUpdate(delta);
				delta = 0.0f;
				++updates;
			}

			++frames;
			OnRender();
			m_MainWindow->Update();

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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyEvent));

		for (auto layer = begin(m_pLayers);
			layer != end(m_pLayers);
			++layer)
		{
			(*layer)->OnEvent(event);
		}
	}

	void Application::OnUpdate(f32 deltaTime)
	{
		for (u64 i = 0; i < m_pLayers.size(); ++i)
		{
			m_pLayers[i]->OnUpdate(deltaTime);
		}
	}

	void Application::OnRender()
	{
		for(s64 i = m_pLayers.size() - 1; i >= 0; --i)
		{
			m_pLayers[i]->OnRender();
		}
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