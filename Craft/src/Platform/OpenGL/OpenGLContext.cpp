#include "crpch.h"
#include "OpenGLContext.h"
#include "Platform\Windows\Win32OpenGL\Win32OpenGL.h"

namespace Craft
{
	OpengGLContext::OpengGLContext(WindowHandle handle) : 
		m_WindowHandle(handle)
	{
	}

	void OpengGLContext::Init()
	{
		if (!Win32InitOpenGL(m_WindowHandle))
		{
			CR_CORE_ERROR("Can't init Windows-OpenGL");
		}
	}

	void OpengGLContext::SwapBuffers()
	{
		Win32SwapBuffers(m_WindowHandle);
	}
}