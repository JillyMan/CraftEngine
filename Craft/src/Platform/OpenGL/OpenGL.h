#pragma once

//#include "Glew\Glew.h"

#include <glad\glad.h>
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

	opengl_info glGetInfo(bool ModernContext = true);
	bool glInit(WindowHandle handle);
	void glSwapBuffers();
	void glVSync(bool enabled);
	void glDestroyContext();
}