#include "crpch.h"

#include "CraftGLContext.h"

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
		//Craft no support swap buffers
	}
}