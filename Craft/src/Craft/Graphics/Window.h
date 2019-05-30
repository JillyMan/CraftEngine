#pragma once

#include "crpch.h"

namespace Craft
{
	struct WindowSetting
	{
		int Width, Height;
		bool IsFullscreen;

		//My default values
		WindowSetting() :
			Width(1024), Height(768), IsFullscreen(true)
		{
		}
	};

	class CRAFT_API Window
	{
	private: 
		static std::map<void*, Window*> s_Handles;
		WindowSetting& m_Setting;
		String m_Title;
		bool m_Closed;
		void* m_Handle;

	public:
		Window(String& title, WindowSetting& setting);
		~Window();

		bool Closed();
		void Clear();
		void Update();
		void ToogleFullScreenMode();

		const void* GetNativeWindowHandle();

	private:
		bool Init();
		bool PlatformInit();
		void PlatformUpdate();
		void PlatformToogleFullScreenMode();

	public:
		static void RegisterWindowClass(void* handle, Window* window);
		static Window* GetWindowClass(void* handle);
	};
}