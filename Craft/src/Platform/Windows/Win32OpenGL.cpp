#include "crpch.h"

#include "Platform\OpenGL\OpenGL.h"

namespace Craft
{
	static HDC WindowDC;

	static void InitOpenGLExtensions(void)
	{
		WNDCLASS tempWindowClass = {};
		tempWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		tempWindowClass.lpfnWndProc = DefWindowProc;
		tempWindowClass.hInstance = GetModuleHandle(0);
		tempWindowClass.lpszClassName = "Temp window";

		CR_ASSERT(RegisterClass(&tempWindowClass), "Can't register temp window class");

		HWND tempWindow = CreateWindowExA(
			0,
			tempWindowClass.lpszClassName,
			"Temp OpenGL Window",
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			tempWindowClass.hInstance,
			0
		);

		CR_ASSERT(tempWindow, "Failed to create temp window");

		HDC tempDC = GetDC(tempWindow);

		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int pixelFormat = ChoosePixelFormat(tempDC, &pfd);

		CR_ASSERT(pixelFormat, "Failed to find a suitable pixel format.");
		CR_ASSERT(SetPixelFormat(tempDC, pixelFormat, &pfd), "Failed to set the pixel format.");

		HGLRC tempContext = wglCreateContext(tempDC);

		CR_ASSERT(tempContext, "Failed to create a dummy OpenGL rendering context.");
		CR_ASSERT(wglMakeCurrent(tempDC, tempContext), "Failed to activate dummy OpenGL rendering context.");
		CR_ASSERT(pfnGLLoad(), "Failed to load PFN GL.");

		wglMakeCurrent(tempDC, tempContext);
		wglDeleteContext(tempContext);
		ReleaseDC(tempWindow, tempDC);
		DestroyWindow(tempWindow);
	}	

	bool glInit(WindowHandle window)
	{
		InitOpenGLExtensions();

		int pixelFormatAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
			WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB,         32,
			WGL_DEPTH_BITS_ARB,         24,
			WGL_STENCIL_BITS_ARB,       8,
			0
		};

		int pixelFormat;
		UINT numFormats;
		WindowDC = GetDC(window);
		wglChoosePixelFormatARB(WindowDC, pixelFormatAttribs, 0, 1, &pixelFormat, &numFormats);

		CR_ASSERT(numFormats, "Failed select opengl pixel format");

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(WindowDC, pixelFormat, sizeof(pfd), &pfd);
		CR_ASSERT(SetPixelFormat(WindowDC, pixelFormat, &pfd), "Failed to set opengl pixel format")

		int gl46Attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		HGLRC glContext = wglCreateContextAttribsARB(WindowDC, 0, gl46Attribs);
		CR_ASSERT(glContext, "Failed create opengl 4.6 context");
		CR_ASSERT(wglMakeCurrent(WindowDC, glContext), "Failed to activate opengl 4.6 rendering context");

		return true;
	}

	void glSwapBuffers()
	{
		SwapBuffers(WindowDC);
	}

	void glVSync(bool enabled)
	{
		wglSwapIntervalEXT(enabled ? 1 : 0);
	}

	void glDestroyContext()
	{
		HGLRC OpenGLRC = wglGetCurrentContext();
		wglDeleteContext(OpenGLRC);
	}

	opengl_info glGetInfo()
	{
		opengl_info Result = {};

		Result.ModernContext = true;
		Result.Vendor = (char*)glGetString(GL_VENDOR);
		Result.Version = (char*)glGetString(GL_VERSION);
		Result.Renderer = (char*)glGetString(GL_RENDERER);
		Result.Extensions = (char*)glGetString(GL_EXTENSIONS);

		return Result;
	}
}