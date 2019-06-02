#pragma once

#include "Window.h"
namespace Craft
{
	class WindowManager
	{
	private:
		static std::map<WindowHandle, Window*> s_Handles;

	public:
		static Window* Create(WindowSetting& setting = WindowSetting());
		static void Destroy(Window* window);

		static Window* GetWindowClass(WindowHandle handle);
		static void RegisterWindowClass(WindowHandle handle, Window* window);
	};
}