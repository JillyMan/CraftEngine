#pragma once
#include <gl\GL.h>

namespace Craft
{
	static HDC WindowDC;

	bool Win32InitOpenGL(HWND Window)
	{
		bool Result = true;
		PIXELFORMATDESCRIPTOR DesiredPixelFormat;
		DesiredPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		DesiredPixelFormat.nVersion = 1;
		DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
		DesiredPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		DesiredPixelFormat.cColorBits = 32;
		DesiredPixelFormat.cAlphaBits = 8;
		DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

		WindowDC = GetDC(Window);
		u32 SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
		PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
		DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
		SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);
		HGLRC OpenGLRC = wglCreateContext(WindowDC);

		if (!wglMakeCurrent(WindowDC, OpenGLRC))
		{
			Result = false;
		}
		
		return Result;
	}

	void Win32SwapBuffers(HWND Window)
	{		
		glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(10.0f, 10.f);
		glVertex2f(100.0f, 100.f);
		glEnd();

		glDrawArrays(GL_LINES, 0, 1);

		SwapBuffers(WindowDC);
	}
}