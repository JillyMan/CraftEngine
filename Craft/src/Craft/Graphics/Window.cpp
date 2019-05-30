#include "crpch.h"
#include "Window.h"

namespace Craft
{
	std::map<void*, Window*> Window::s_Handles;

	Window::Window(String& title, WindowSetting& setting) :
		m_Title(title), m_Setting(setting)
	{
		if (!Init())
		{
			CR_ERROR("Oops, window not inititialize !!");
			return;
		}
		CR_WARN("Window inititialize");
	}

	Window::~Window()
	{

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

	void Window::ToogleFullScreenMode()
	{
		PlatformToogleFullScreenMode();
	}

	const void* Window::GetNativeWindowHandle()
	{
		return m_Handle;
	}

	bool Window::Closed()
	{
		return m_Closed;
	}

	void Window::RegisterWindowClass(void* handle, Window* window)
	{
		s_Handles[handle] = window;
	}

	Window* Window::GetWindowClass(void* handle)
	{
		return s_Handles[handle];
	}
}