#include "crpch.h"

#include <gl/GL.h>
#include "Glew.h"

#if defined(_WIN32) || defined(__CYGWIN__)

#include <windows.h>
static HMODULE libGL;

#endif

static int open_gl(void)
{
	libGL = LoadLibraryW(L"opengl32.dll");
	if (libGL != NULL)
	{
		void(*tmp)(void);
		tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
		glewGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)tmp;
		return glewGetProcAddressPtr != NULL;
	}

	return 0;
}

static void close_gl(void)
{
	if (libGL != NULL)
	{
		FreeLibrary((HMODULE)libGL);
		libGL = NULL;
	}
}

static void* get_proc(const char *name)
{
	void* result = NULL;
	if (libGL == NULL) return NULL;

	if (glewGetProcAddressPtr != NULL) {
		result = glewGetProcAddressPtr(name);
	}
	if (result == NULL) {
		result = (void*)GetProcAddress((HMODULE)libGL, name);
	}

	return result;
}

PFNWGLSWAPINTERVALFARPROC glSwapInterval = NULL;

PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;

PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = NULL;

void glewLoadGLLoader(GLEWloadproc load)
{
#if defined(_WIN32) || defined(__CYGWIN__)
	glSwapInterval =(PFNWGLSWAPINTERVALFARPROC)load("glSwapInterval");
#else
#	error not supported
#endif

	glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
	glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource ");
	glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
	glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader ");

	glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers ");
	glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)load("glBindVertexBuffer");
}

int glewLoadGL(void)
{
	//TODO(status) clear TRASH
	int status = 1;

	if (open_gl())
	{
		glewLoadGLLoader(&get_proc);
		close_gl();
	}

	return status;
}