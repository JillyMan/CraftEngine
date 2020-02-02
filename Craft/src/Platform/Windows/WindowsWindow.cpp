#include "crpch.h"

#include "WindowsWindow.h"
#include "Craft/Event/KeyEvent.h"
#include "Craft/Event/MouseEvent.h"
#include "Craft/Event/ApplicationEvent.h"
#include "Craft/Window/WindowManager.h"

//--------delete dependency
#include "Platform/OpenGL/OpenGLContext.h"
#include "imgui.h"
#include "Platform/Windows/ImGuiImplWin32.h"
//--------

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace Craft {

	WNDCLASS WindowsWindow::s_WindowClass = {};
	BOOL WindowsWindow::s_WindowClassInit = false;
	HINSTANCE WindowsWindow::s_HInstance = GetModuleHandle(0);
	LPCSTR WindowsWindow::s_WindowClassName = "Craft Engine Window";

	WindowsWindow::WindowsWindow(WindowSetting& setting)
	{
		m_Setting = setting;
		m_IsClosed = false;
		m_InputHandler = new Input::InputHandler();
		CR_ASSERT(Init(), "Window init == false, why ??");
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
			CR_CORE_ERROR("Can't register window class");
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
			CR_CORE_INFO("Can't create Window handle. [error code = %d]", GetLastError());
			return false;
		}

		WindowManager::RegisterWindowClass(m_WindowHandle, this);

//--------------------
		Graphics::GLInitData setting; 
		setting.VSync = m_Setting.IsVSync;
		setting.Handle = m_WindowHandle;
		setting.DebugMode = true;
		m_GraphicsContext = new Graphics::OpengGLContext(setting);
//--------------------
		m_GraphicsContext->Init();

		ShowWindow(m_WindowHandle, SW_SHOW);
		UpdateWindow(m_WindowHandle);

		return true;
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(m_WindowHandle);
		delete m_InputHandler;
		delete m_GraphicsContext;
		CR_CORE_FATAL("Window close");
	}

	void WindowsWindow::SetTitle(String& title)
	{
		m_Setting.Title = title;
		SetWindowTextA(m_WindowHandle, title.c_str());
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Setting.IsVSync = enabled;
		m_GraphicsContext->VSync(enabled);
	}

	bool WindowsWindow::IsVSync()
	{
		return m_Setting.IsVSync;
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
		window->m_InputHandler->OnKeyPressed(vkCode);
		window->OnEvent(KeyPressedEvent(vkCode, 0));
	}

	void OnKeyReleased(WindowsWindow* window, u64 vkCode)
	{
		window->m_InputHandler->OnKeyReleased(vkCode);
		window->OnEvent(KeyReleasedEvent(vkCode));
	}

	void OnResizeWindow(WindowsWindow* window, u32 width, u32 height)
	{
		window->OnEvent(WindowResizeEvent(width, height));
	}

	void OnMouseMove(WindowsWindow* window, s32 x, s32 y)
	{	
		window->m_InputHandler->SetMousePosition(x, y);
		window->OnEvent(MouseMovedEvent(x, y));
	}

	void OnMouseWheel(WindowsWindow* window, s32 zDelta) 
	{
		//window->m_InputHandler->SetMouseWheelPos(xPos, yPos);
		window->OnEvent(MouseScrollWheelEvent(zDelta));
	}

	void OnMouseButtonPressed(WindowsWindow* window, s32 x, s32 y, u32 button)
	{
		window->m_InputHandler->OnMouseKeyPressed(button);
		window->OnEvent(MouseButtonPressedEvent(x, y, button));
	}

	void OnMouseButtonReleased(WindowsWindow* window, s32 x, s32 y, u32 button)
	{
		window->m_InputHandler->OnMouseKeyReleased(button);
		window->OnEvent(MouseButtonReleasedEvent(x, y, button));
	}

	void OnWindowClose(WindowsWindow* window)
	{
		window->OnEvent(WindowCloseEvent());
	}

	LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT Result = ImGui_ImplWin32_WndProcHandler(hWindow, uMsg, wParam, lParam);
		WindowsWindow* window = (WindowsWindow*)WindowManager::GetWindowClass(hWindow);

		switch (uMsg)
		{
			case WM_CREATE:
			{
				CR_CORE_INFO("Window is created");
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
			case WM_MOUSEWHEEL: 
			{
				s32 zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
				OnMouseWheel(window, zDelta/abs(zDelta));
				break;
			}
			case WM_LBUTTONDOWN:
			{
				OnMouseButtonPressed(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), VK_LBUTTON);
				break;
			}
			case WM_LBUTTONUP: {
				OnMouseButtonReleased(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), VK_LBUTTON);
				break;
			}
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				OnMouseButtonPressed(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
				break;
			}
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
			{
				OnMouseButtonReleased(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
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