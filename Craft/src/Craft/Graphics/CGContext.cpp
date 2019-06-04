#include "crpch.h"

#include "CGContext.h"

namespace Craft { namespace Graphics {

	CGContext::CGContext(WindowHandle windowHandle) :
		m_WindowHandle(windowHandle)
	{
	}

	CGContext::~CGContext()
	{
	}

	void CGContext::Init()
	{
		CR_CORE_INFO("Craft-Graphics context init");
	}
	
	void CGContext::SwapBuffers() 
	{
	}
}}