#include "crpch.h"
#include "WindowManager.h"

#if CRAFT_PLATFORM_WINDOWS
	#include "Platform\Windows\WindowsWindow.h"
#endif

namespace Craft
{
	std::map<WindowHandle, Window*> WindowManager::s_Handles;

	void WindowManager::RegisterWindowClass(WindowHandle handle, Window* window)
	{
		s_Handles[handle] = window;
	}

	Window* WindowManager::GetWindowClass(WindowHandle handle)
	{
		return s_Handles[handle];
	}

	Window* WindowManager::Create(WindowSetting& setting)
	{
#if CRAFT_PLATFORM_WINDOWS
		return new WindowsWindow(setting);
#elif
		return NULL;
#endif
	}

	void WindowManager::Destroy(Window* window)
	{
		delete window;
	}
}