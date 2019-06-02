#include "crpch.h"

#include "CGContext.h"

namespace Craft { namespace Graphics {

	CGContext::CGContext()
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