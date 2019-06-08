#include "crpch.h"

#include "CraftGLContext.h"
#include "Craft\Graphics\CraftGL\CraftGL.h"

namespace Craft {

	CraftGLContext::CraftGLContext(WindowHandle windowHandle) :
		m_WindowHandle(windowHandle)
	{
	}

	CraftGLContext::~CraftGLContext()
	{
	}

	void CraftGLContext::Init()
	{
		CR_CORE_INFO("Craft-Graphics context init");
	}
	
	void CraftGLContext::SwapBuffers()
	{
	}
}