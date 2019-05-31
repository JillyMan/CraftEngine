#pragma once

#include "crpch.h"

#include "Craft/Event/Event.h"
#include "Craft/Graphics/WindowStyle.h"
#include "Craft/Graphics/WindowHandle.h"

namespace Craft
{
	struct CRAFT_API WindowSetting
	{
		s32 Width, Height;
		bool IsFullscreen;
		u32 Style;
		
		WindowSetting() :
			Width(1024),
			Height(768),
			IsFullscreen(false),
			Style(Style::Default)
		{
		}
	};

	class CRAFT_API Window
	{
	private:
		static std::map<WindowHandle, Window*> s_Handles;
		WindowSetting& m_Setting;
		String m_Title;
		bool m_Running;
		WindowHandle m_Handle;

	public:
		Window(String& title, WindowSetting& setting);
		~Window();

		void Close();
		void Clear();
		void Update();
		bool IsClose();
		const WindowHandle GetWindowHandle();

		void ToogleFullScreenMode();
		void SetTitle(String& title);

	private:
		bool Init();
		bool PlatformInit();
		void PlatormClose();
		void PlatformUpdate();

	public:
		static void RegisterWindowClass(WindowHandle handle, Window* window);
		static Window* GetWindowClass(WindowHandle handle);
	};
}