#include "crpch.h"

#include "OpenGL.h"
#include "OpenGLContext.h"

namespace Craft { namespace Graphics {

	static void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam)
	{
		String sourceStr;
		switch (source) {
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sourceStr = "WindowSys";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			sourceStr = "App";
			break;
		case GL_DEBUG_SOURCE_API:
			sourceStr = "OpenGL";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sourceStr = "ShaderCompiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sourceStr = "3rdParty";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			sourceStr = "Other";
			break;
		default:
			sourceStr = "Unknown";
		}

		String typeStr;
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			typeStr = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			typeStr = "Deprecated";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			typeStr = "Undefined";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			typeStr = "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			typeStr = "Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			typeStr = "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			typeStr = "PushGrp";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			typeStr = "PopGrp";
			break;
		case GL_DEBUG_TYPE_OTHER:
			typeStr = "Other";
			break;
		default:
			typeStr = "Unknown";
		}

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			CR_CORE_ERROR("%s:%s[High](%d): %s", sourceStr.c_str(), typeStr.c_str(),
				id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			CR_CORE_WARN("%s:%s[Medium](%d): %s", sourceStr.c_str(), typeStr.c_str(),
				id, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			CR_CORE_WARN("%s:%s[Low](%d): %s", sourceStr.c_str(), typeStr.c_str(),
				id, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			CR_CORE_TRACE("%s:%s[Notification](%d): %s", sourceStr.c_str(), typeStr.c_str(),
				id, message);
			break;
		default:
			CR_CORE_TRACE("%s:%s[Unknown](%d): %s", sourceStr.c_str(), typeStr.c_str(),
				id, message);
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
		VSync(m_InitData.VSync);

		opengl_info info = glGetInfo();
		CR_CORE_TRACE("OpenGL init successed: ");
		CR_CORE_TRACE("Vendor: %s", info.Vendor);
		CR_CORE_TRACE("Version: %s", info.Version);
		CR_CORE_TRACE("Render device: %s", info.Renderer);

		GLint shaderInputs;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &shaderInputs);
		CR_CORE_INFO("MAX shader inputs: %d", shaderInputs);

		if (m_InitData.DebugMode) {
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(MessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
				GL_DONT_CARE, 0, NULL, GL_TRUE);
		}
	}

	void OpengGLContext::SwapBuffers()
	{
		glSwapBuffers();
	}

	void OpengGLContext::VSync(bool enabled)
	{
		glVSync(enabled);
	}
}}