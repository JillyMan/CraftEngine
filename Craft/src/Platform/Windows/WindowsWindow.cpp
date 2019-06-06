#include "crpch.h"

#include "WindowsWindow.h"

#include "Craft/Window/WindowManager.h"

#include "Craft/Event/KeyEvent.h"
#include "Craft/Event/MouseEvent.h"
#include "Craft/Event/ApplicationEvent.h"

#include "Craft/Graphics/CraftGL/CraftGLContext.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

// or use GetModuleHandle(NULL) - ??
#define HINS_THISCOMPONENT ((HINSTANCE)&__ImageBase)

namespace Craft {

	WNDCLASS WindowsWindow::s_WindowClass = {};
	BOOL WindowsWindow::s_WindowClassInit = false;
	HINSTANCE WindowsWindow::s_HInstance = HINS_THISCOMPONENT;
	LPCSTR WindowsWindow::s_WindowClassName = "Craft Engine Window";

	WindowsWindow::WindowsWindow(WindowSetting& setting)
	{
		m_Setting = setting;
		m_IsClosed = false;

		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Update()
	{
		MSG Message;
		while (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		m_GraphicsContext->SwapBuffers();
	}

	bool WindowsWindow::Init()
	{
		if (WindowClassInit() == 0)
		{
			CR_ERROR("Can't register window class");
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

		m_WindowHandle = CreateWindowExA(
			dwExStyle,
			s_WindowClass.lpszClassName,
			m_Setting.Title.c_str(),
			dwStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			desiredWindowSize.right - desiredWindowSize.left,
			desiredWindowSize.bottom - desiredWindowSize.top,
			NULL,
			NULL,
			s_HInstance,
			NULL);

		if (!m_WindowHandle)
		{
			int error = GetLastError();
			String str("Can't create Window handle error=");
			str += std::to_string(error);
			CR_INFO(str);
			return false;
		}

		WindowManager::RegisterWindowClass(m_WindowHandle, this);
		ShowWindow(m_WindowHandle, SW_SHOW);

		//TODO: Create graphics factory!
		m_GraphicsContext = new CraftGLContext(m_WindowHandle);
		m_GraphicsContext->Init();

		return true;
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(m_WindowHandle);
		CR_FATAL("Window close");
	}

	void WindowsWindow::SetTitle(String& title)
	{
		m_Setting.Title = title;
		SetWindowTextA(m_WindowHandle, title.c_str());
	}

	void WindowsWindow::ToogleFullScreenMode()
	{
		DWORD dwStyle = GetWindowLong(m_WindowHandle, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW) 
		{
			MONITORINFO mi = { sizeof(mi) };
			if (GetWindowPlacement(m_WindowHandle, &m_PrevPlacement) &&
				GetMonitorInfo(MonitorFromWindow(m_WindowHandle,
					MONITOR_DEFAULTTOPRIMARY), &mi)) 
			{
				SetWindowLong(m_WindowHandle, GWL_STYLE,
					dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(m_WindowHandle, HWND_TOP,
					mi.rcMonitor.left, mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		}
		else {
			SetWindowLong(m_WindowHandle, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
			SetWindowPlacement(m_WindowHandle, &m_PrevPlacement);
			SetWindowPos(m_WindowHandle, NULL, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}

	bool WindowsWindow::WindowClassInit()
	{
		if (s_WindowClassInit)
		{
			return false;
		}

		s_WindowClass.hInstance = s_HInstance;
		s_WindowClass.lpfnWndProc = WindowProc;
		s_WindowClass.hbrBackground = WHITE_BRUSH;
		s_WindowClass.lpszClassName = s_WindowClassName;
		s_WindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		s_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		s_WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		s_WindowClassInit = RegisterClass(&s_WindowClass);
		return s_WindowClassInit;
	}

	void WindowsWindow::OnEvent(Event& event)
	{
		m_EventCallback(event);
	}

	void OnKeyPressed(WindowsWindow* window, u64 vkCode)
	{
		KeyPressedEvent kpe(vkCode, 0);
		window->OnEvent(kpe);
	}

	void OnKeyReleased(WindowsWindow* window, u64 vkCode)
	{
		KeyReleasedEvent kre(vkCode);
		window->OnEvent(kre);
	}
	
	void OnResizeWindow(WindowsWindow* window, u32 width, u32 height)
	{
		WindowResizeEvent wre(width, height);
		window->OnEvent(wre);
	}

	void OnMouseMove(WindowsWindow* window, s32 x, s32 y)
	{
		MouseMovedEvent mme(x, y);
		window->OnEvent(mme);
	}

	void OnMouseButtonPressed(WindowsWindow* window, u32 button)
	{
		MouseButtonPressedEvent mbpe(button);
		window->OnEvent(mbpe);
	}

	void OnMouseButtonReleased(WindowsWindow* window, u32 button)
	{
		MouseButtonReleasedEvent mbre(button);
		window->OnEvent(mbre);
	}

	void OnWindowClose(WindowsWindow* window)
	{
		WindowCloseEvent mce;
		window->OnEvent(mce);
	}

	LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT Result = 0;
		WindowsWindow* window = (WindowsWindow*)WindowManager::GetWindowClass(hWindow);

		switch (uMsg)
		{
			case WM_CREATE:
			{
				CR_INFO("Window is created");
				break;
			}
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWindow, &ps);
				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
				FillRect(hdc, &ps.rcPaint, brush);
				EndPaint(hWindow, &ps);
				break;
			}
			case WM_CLOSE:
			{
				OnWindowClose(window);
				break;
			}
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				u64 VKCode = wParam;
				bool WasDown = ((lParam & (1 << 30)) != 0);
				bool IsDown = ((lParam & (1 << 31)) == 0);

				if (IsDown != WasDown)
				{
					if (IsDown)
					{
						OnKeyPressed(window, VKCode);
					}
					else if (WasDown)
					{
						OnKeyReleased(window, VKCode);
					}
				}

				break;
			}
			case WM_MOUSEMOVE:
			{
				OnMouseMove(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			{
				CR_INFO("mouse button click");
				break;
			}
			case WM_SIZE:
			{
				if (window != nullptr)
				{
					OnResizeWindow(window, LOWORD(lParam), HIWORD(lParam));
				}
				break;
			}
			default:
			{
				Result = DefWindowProc(hWindow, uMsg, wParam, lParam);
				break;
			}
		}

		return Result;
	}
}