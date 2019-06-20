#include "crpch.h"

#include "OpenGL.h"
#include "OpenGLContext.h"

namespace Craft
{
	static void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam)
	{
		if (type == GL_DEBUG_TYPE_ERROR)
		{
			CR_ERROR("%s [type 0x%x], [severity = 0x%x], [message=%s]\n", 
				"** GL ERROR **", type, severity, message);
		}
		else
		{
			CR_INFO("GL CALLBACK: [type = 0x%x], [severity = 0x%x] \t \nmessage = %s\n", type, severity, message);
		}
	}

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
		CR_ASSERT(glInit(m_InitData.Handle), "Can't init Windows-OpenGL");
		glVSync(m_InitData.VSync);

		opengl_info info = glGetInfo();
		CR_CORE_TRACE("OpenGL init successed: ");
		CR_CORE_TRACE("Vendor: %s", info.Vendor);
		CR_CORE_TRACE("Version: %s", info.Version);
		CR_CORE_TRACE("Render device: %s", info.Renderer);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

	}

	void OpengGLContext::SwapBuffers()
	{
		glSwapBuffers();
	}
}