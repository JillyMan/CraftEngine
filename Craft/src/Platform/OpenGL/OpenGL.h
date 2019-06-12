#pragma once

#include "Glew\Glew.h"
//#include <glad\glad.h>

//#include <gl/GL.h>
//#include <gl/WGLext.h>
//#include <gl/GLext.h>

#include <Craft\Window\WindowHandle.h>

namespace Craft
{
	struct opengl_info
	{
		bool ModernContext;
		char* Vendor;
		char* Renderer;
		char* Version;
		char* ShadingLanguageVersion;
		char* Extensions;
	};

	opengl_info glGetInfo();
	bool glInit(WindowHandle handle);
	void glSwapBuffers();
	void glVSync(bool enabled);
	void glDestroyContext();
}