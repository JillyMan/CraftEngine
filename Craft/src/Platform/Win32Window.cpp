#include "crpch.h"
#include "Craft/Graphics/Window.h"
#include "Craft/Graphics\WindowStyle.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

// or use GetModuleHandle(NULL) - ??
#define HINS_THISCOMPONENT ((HINSTANCE)&__ImageBase)

namespace Craft {

	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
	static HINSTANCE s_HInstance;
	static LPCSTR WindowClassName = "Craft Engine Window";
	static bool IsPlatformInit = false;
	static WNDCLASS WinClass = {};

	void Window::SetTitle(String& title)
	{
		SetWindowTextA(m_Handle, title.c_str());
	}

	static bool WinClassInit()
	{
		s_HInstance = HINS_THISCOMPONENT;

		WinClass.hInstance = s_HInstance;
		WinClass.lpfnWndProc = WindowProc;
		WinClass.hbrBackground = WHITE_BRUSH;
		WinClass.lpszClassName = WindowClassName;
		WinClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WinClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if (!RegisterClass(&WinClass))
		{
			CR_CORE_INFO("Can't regiser window class");
			return false;
		}
		IsPlatformInit = true;
		return true;
	}

	//work only with anci string, unicode not support
	bool Window::PlatformInit()
	{
		if (!IsPlatformInit && !WinClassInit())
		{
			return false;
		}

		DWORD dwStyle = WS_VISIBLE;
		
		u32 style = m_Setting.Style;
		if (style == Style::None)
		{
			dwStyle |= WS_POPUP;
		}
		else
		{
			if (style & Style::Titlebar)	dwStyle |= WS_CAPTION | WS_MINIMIZEBOX;
			if (style & Style::Resize)		dwStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
			if (style & Style::Close)		dwStyle |= WS_SYSMENU;
		}
		
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		RECT desiredWindowSize = { 0, 0, m_Setting.Width, m_Setting.Height };
		AdjustWindowRectEx(&desiredWindowSize, dwStyle, FALSE, dwExStyle);

		m_Handle = CreateWindowExA(
			dwExStyle,
			WinClass.lpszClassName,
			m_Title.c_str(),
			dwStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			desiredWindowSize.right - desiredWindowSize.left,
			desiredWindowSize.bottom - desiredWindowSize.top,
			NULL,
			NULL,
			s_HInstance,
			NULL);

		if (!m_Handle)
		{
			int error = GetLastError();
			String str("Can't create Window handle error=");
			str += std::to_string(error);
			CR_CORE_INFO(str);
			return false;
		}

		//here -> need initialize render context!!!!

		RegisterWindowClass(m_Handle, this);
		ShowWindow(m_Handle, SW_SHOW);

		return true;
	}

	void Window::PlatformUpdate()
	{
		MSG Message;
		while (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			if (Message.message == WM_CLOSE)
			{
				Close();
				return;
			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	void Window::ToogleFullScreenMode()
	{
	}

	void Window::PlatormClose()
	{
		DestroyWindow(m_Handle);
		CR_CORE_INFO("Window close");
	}

	LRESULT CALLBACK WindowProc(HWND window, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT Result = 0;
		switch (uMsg)
		{
			case WM_CREATE:
			{
				CR_CORE_INFO("Window is created");
				break;
			}
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(window, &ps);
				FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_GRADIENTACTIVECAPTION + 1);
				EndPaint(window, &ps);
				break;
			}
			case WM_CLOSE:
			{
				//Window::GetWindowClass(window)->Close();
				break;
			}
			default:
			{
				Result = DefWindowProc(window, uMsg, wParam, lParam);
				break;
			}
		}
		return Result;
	}
}