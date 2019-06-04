#pragma once

#include "Craft\Core.h"
#include "Craft\Window\Window.h"
#include "Craft\Graphics\GraphicsContext.h"

namespace Craft
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowSetting& setting);
		~WindowsWindow();

		void Update();
		void ToogleFullScreenMode();
		void SetTitle(String& title);

		u32 GetWidth() override { return m_Setting.Width; }
		u32 GetHeight() override { return m_Setting.Height; }
		String GetTitle() override { return m_Setting.Title; }
		WindowHandle GetWindowHandle() override { return m_WindowHandle; }

		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }

	private:
		virtual bool Init();
		virtual void Shutdown();

	private:
		Graphics::GraphicsContext* m_GraphicsContext;

		bool m_IsClosed;
		WindowSetting m_Setting;
		EventCallbackFn m_EventCallback;

		HWND m_WindowHandle;
		WINDOWPLACEMENT m_PrevPlacement;

	private:
		void OnEvent(Event& event);

		friend void OnKeyPressed(WindowsWindow* window, u64 vkCode);
		friend void OnKeyReleased(WindowsWindow* window, u64 vkCode);

		friend void OnWindowClose(WindowsWindow* window);

		friend void OnResizeWindow(WindowsWindow* window, u32 width, u32 height);
		friend void OnMouseMove(WindowsWindow* window, s32 x, s32 y);
		friend void OnMouseButtonPressed(WindowsWindow* window, u32 button);
		friend void OnMouseButtonReleased(WindowsWindow* window, u32 button);

		friend LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool WindowClassInit();
		
		static BOOL s_WindowClassInit;
		static WNDCLASS s_WindowClass;
		static HINSTANCE s_HInstance;
		static LPCSTR s_WindowClassName;
	};
}