#include "crpch.h"

#include "Glew.h"

#if defined(_WIN32) || defined(__CYGWIN__)

#include <windows.h>
static HMODULE libGL;

#endif

PFNGLCREATEPROGRAMPROC _glCreateProgram = NULL;
PFNGLCREATEBUFFERSPROC _glCreateBuffers = NULL;
PFNGLCREATEVERTEXARRAYSPROC _glCreateVertexArrays = NULL;
PFNGLBINDBUFFERPROC _glBindBuffer = NULL;
PFNGLBUFFERDATAPROC _glBufferData = NULL;
PFNGLBINDVERTEXARRAYPROC _glBindVertexArray = NULL;

PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray = NULL;

PFNGLCREATESHADERPROC _glCreateShader = NULL;
PFNGLSHADERSOURCEPROC _glShaderSource = NULL;
PFNGLCOMPILESHADERPROC _glCompileShader = NULL;
PFNGLATTACHSHADERPROC _glAttachShader = NULL;
PFNGLLINKPROGRAMPROC _glLinkProgram = NULL;
PFNGLDELETESHADERPROC _glDeleteShader = NULL;
PFNGLUSEPROGRAMPROC _glUseProgram = NULL;
PFNGLDELETEPROGRAMPROC _glDeleteProgram = NULL;

PFNGLDRAWARRAYSEXTPROC _glDrawArraysEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC _wglSwapIntervalEXT = NULL;

PFNGLDELETEVERTEXARRAYSPROC _glDeleteVertexArrays = NULL;
PFNGLDELETEBUFFERSPROC _glDeleteBuffers = NULL;

PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormatARB = NULL;

PFNGLDEBUGMESSAGECALLBACKPROC _glDebugMessageCallback = NULL;
PFNGLGETSHADERIVPROC _glGetShaderiv = NULL;
PFNGLGETPROGRAMIVPROC _glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC _glGetShaderInfoLog = NULL;
PFNGLGETPROGRAMINFOLOGPROC _glGetProgramInfoLog = NULL;

void glPlatformLoad(GLEWloadproc load)
{
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
}

void loadPFN(GLEWloadproc load)
{
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
	glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
	glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)load("glCreateVertexArrays");
	glCreateBuffers = (PFNGLCREATEBUFFERSPROC)load("glCreateBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
	glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
	glDrawArrays = (PFNGLDRAWARRAYSEXTPROC)load("glDrawArrays");

	glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)load("glDebugMessageCallback");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetShaderInfoLog ");
}

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

int pfnGLLoad(void)
{
	int status = open_gl();
	
	if (status)
	{
		glPlatformLoad(&get_proc);
		loadPFN(&get_proc);
		close_gl();
	}
	return status;
}