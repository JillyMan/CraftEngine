#include "crpch.h"

#include "Platform\OpenGL\OpenGL.h"

namespace Craft
{
	bool glInit(WindowHandle Window)
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

		HDC WindowDC = GetDC(Window);
		u32 SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
		PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
		DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
		SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);
		HGLRC OpenGLRC = wglCreateContext(WindowDC);

		if (!wglMakeCurrent(WindowDC, OpenGLRC))
		{
			Result = false;
		}

		glewInit();

		return Result;
	}

	void glSwapBuffers()
	{
		HDC WindowDC = wglGetCurrentDC();
		SwapBuffers(WindowDC);
	}

	void glVSync(bool enabled)
	{

	}

	void glDestroyContext()
	{
		HGLRC OpenGLRC = wglGetCurrentContext();
		wglDeleteContext(OpenGLRC);
		//TODO: (debut this moment)
		HDC WindowDC = wglGetCurrentDC();
	}

	opengl_info glGetInfo(bool ModernContext)
	{
		opengl_info Result = {};

		Result.ModernContext = ModernContext;
		Result.Vendor = (char*)glGetString(GL_VENDOR);
		Result.Version = (char*)glGetString(GL_VERSION);
		Result.Renderer = (char*)glGetString(GL_RENDERER);
		Result.Extensions = (char*)glGetString(GL_EXTENSIONS);

		return Result;
	}
}