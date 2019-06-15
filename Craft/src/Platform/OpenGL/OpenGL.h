#pragma once

#include "Glew\Glew.h"
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