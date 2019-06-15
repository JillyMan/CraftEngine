#include "crpch.h"

#include "Platform\OpenGL\OpenGL.h"

namespace Craft
{
	bool glInit(WindowHandle Window)
	{
		bool Result = false;
		PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
		DesiredPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		DesiredPixelFormat.nVersion = 1;
		DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
		DesiredPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		DesiredPixelFormat.cColorBits = 32;
		DesiredPixelFormat.cAlphaBits = 8;
		DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

		HDC WindowDC = GetDC(Window);
		u32 SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
		PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
		DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
		SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);
		HGLRC TempOpenGLRC = wglCreateContext(WindowDC);

		if (wglMakeCurrent(WindowDC, TempOpenGLRC))
		{
			Result = glLoad();
			//if (Result)
			//{
			//	int attributes[] =
			//	{
			//		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			//		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			//		WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			//		0
			//	};

			//	HGLRC OpenGLRC = wglCreateContextAttribsARB(WindowDC, 0, attributes);

			//	if (!OpenGLRC)
			//	{
			//		CR_CORE_INFO("Can't init opengl 4.5 context");
			//		wglDeleteContext(TempOpenGLRC);
			//		return false;
			//	}

			//	if (!wglMakeCurrent(WindowDC, OpenGLRC))
			//	{
			//		wglDeleteContext(TempOpenGLRC);
			//		wglDeleteContext(OpenGLRC);
			//		return false;
			//	}
			//	wglDeleteContext(TempOpenGLRC);
			//}
		}

		return Result;
	}

	void glSwapBuffers()
	{
		HDC WindowDC = wglGetCurrentDC();
		BOOL Result = SwapBuffers(WindowDC);
	}

	void glVSync(bool enabled)
	{
		//if (enabled)
		//{
		//	glSwapInterval(1);
		//}
		//else
		//{
		//	glSwapInterval(0);
		//}
	}

	void glDestroyContext()
	{
		HGLRC OpenGLRC = wglGetCurrentContext();
		wglDeleteContext(OpenGLRC);
		//TODO: (debug this moment)
		HDC WindowDC = wglGetCurrentDC();
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