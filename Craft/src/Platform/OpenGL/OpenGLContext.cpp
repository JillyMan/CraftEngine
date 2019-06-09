#include "crpch.h"

#include "OpenGL.h"
#include "OpenGLContext.h"

namespace Craft
{
	OpengGLContext::OpengGLContext(GLInitData initData) :
		m_InitData(initData)
	{
	}

	OpengGLContext::~OpengGLContext()
	{
		glDestroyContext();
	}

	void OpengGLContext::Init()
	{
		if (!glInit(m_InitData.Handle))
		{
			CR_CORE_ERROR("Can't init Windows-OpenGL");
		}
		else
		{
			opengl_info info = glGetInfo();
			CR_CORE_TRACE("OpenGL init successed: ");
			CR_CORE_TRACE(info.Vendor);
			CR_CORE_TRACE(info.Version);
			CR_CORE_TRACE(info.Renderer);
		//	CR_CORE_TRACE(info.Extensions);
		}

		glVSync(m_InitData.VSync);
	}

	void OpengGLContext::SwapBuffers()
	{
		glSwapBuffers();
	}
}