#include "crpch.h"
#include "Window.h"

namespace Craft
{
	std::map<WindowHandle, Window*> Window::s_Handles;

	Window::Window(String& title, WindowSetting& setting) :
		m_Title(title), m_Setting(setting)
	{
		if (!Init())
		{
			CR_ERROR("Oops, window not inititialize !!");
			return;
		}

		CR_WARN(m_Title + " : - window inititialized");
		m_Running = true;
	}

	Window::~Window()
	{
		if (!IsClose())
		{
			Close();
		}
	}

	bool Window::Init()
	{
		if (!PlatformInit())
		{
			CR_ERROR("Failed in window PlatfromInit()");
			return false;
		}
		return true;
	}

	void Window::Clear()
	{
	}

	void Window::Update()
	{
		PlatformUpdate();
	}

	const WindowHandle Window::GetWindowHandle()
	{
		return m_Handle;
	}

	void Window::Close()
	{
		m_Running = false;
		PlatormClose();
	}

	bool Window::IsClose()
	{
		return !m_Running;
	}

	void Window::RegisterWindowClass(WindowHandle handle, Window* window)
	{
		s_Handles[handle] = window;
	}

	Window* Window::GetWindowClass(WindowHandle handle)
	{
		return s_Handles[handle];
	}
}