#pragma once

#include "crpch.h"

#include "Craft\Event\Event.h"
#include "Craft\Window\WindowStyle.h"
#include "Craft\Window\WindowHandle.h"

namespace Craft
{
	struct CRAFT_API WindowSetting
	{
		bool IsVSync;
		bool IsFullscreen;
		u32 Style;
		s32 Width, Height;
		String Title;

		WindowSetting() :
			Width(1280),
			Height(720),
			IsFullscreen(false),
			Style(Style::Default),
			Title("Craft game engine")
		{
		}
	};

	class CRAFT_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual void Update() = 0;
		virtual void ToogleFullScreenMode() = 0;

		virtual u32 GetWidth() = 0;
		virtual u32 GetHeight() = 0;

		virtual String GetTitle() = 0;
		virtual void SetTitle(String& title) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() = 0;
		virtual void SetEventCallback(const EventCallbackFn& eventCallback) = 0;

		virtual WindowHandle GetWindowHandle() = 0;

	};
}