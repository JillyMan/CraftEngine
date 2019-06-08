#include "crpch.h"

#include <gl/GL.h>
#include "Glew.h"

PFNGLBUFFERDATA glew_glBufferData = NULL;
PFNGLGENBUFFERS glew_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glew_glBindBuffer = NULL;
PFNGLBINDVERTEXBUFFERPROC glew_glBindVertexBuffer = NULL;

static PROC loadProc(const char* stringName)
{
#ifdef CRAFT_PLATFORM_WINDOWS
	return wglGetProcAddress(stringName);
#else
#	error only windows!
#endif
}

void glewInit()
{
	glew_glBufferData = (PFNGLBUFFERDATA)loadProc("glBufferData");
	glew_glGenBuffers = (PFNGLGENBUFFERS)loadProc("glGenBuffers ");
	glew_glBindBuffer = (PFNGLBINDBUFFERPROC)loadProc("glBindBuffer");
	glew_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)loadProc("glBindVertexBuffer");
}
