#include "crpch.h"

#include "Glew.h"

#if defined(_WIN32) || defined(__CYGWIN__)

#include <windows.h>
static HMODULE libGL;

#endif

PFNGLBINDBUFFERPROC _glBindBuffer = NULL;
PFNGLBUFFERDATAPROC _glBufferData = NULL;
PFNGLCREATEPROGRAMPROC _glCreateProgram = NULL;
PFNGLCREATEBUFFERSPROC _glCreateBuffers = NULL;
PFNGLBINDVERTEXARRAYPROC _glBindVertexArray = NULL;
PFNGLCREATEVERTEXARRAYSPROC _glCreateVertexArrays = NULL;

PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray = NULL;

PFNGLUSEPROGRAMPROC _glUseProgram = NULL;
PFNGLLINKPROGRAMPROC _glLinkProgram = NULL;
PFNGLDELETESHADERPROC _glDeleteShader = NULL;
PFNGLCREATESHADERPROC _glCreateShader = NULL;
PFNGLSHADERSOURCEPROC _glShaderSource = NULL;
PFNGLATTACHSHADERPROC _glAttachShader = NULL;
PFNGLDELETEPROGRAMPROC _glDeleteProgram = NULL;
PFNGLCOMPILESHADERPROC _glCompileShader = NULL;
PFNGLVALIDATEPROGRAMPROC _glValidateProgram = NULL;

PFNGLGETUNIFORMLOCATIONARBPROC		_glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC					_glUniform1f = NULL;
PFNGLUNIFORM2FPROC					_glUniform2f = NULL;
PFNGLUNIFORM3FPROC					_glUniform3f = NULL;
PFNGLUNIFORM4FPROC					_glUniform4f = NULL;

PFNGLCREATETEXTURESPROC				_glCreateTextures = NULL;
PFNGLTEXTUREPARAMETERFVPROC			_glTexParameterfv = NULL;
PFNGLTEXTUREPARAMETERIPROC			_glTexParameteri = NULL;


PFNGLDRAWARRAYSEXTPROC _glDrawArraysEXT = NULL;
PFNGLDRAWELEMENTSPROC _glDrawElements = NULL;

PFNWGLSWAPINTERVALEXTPROC _wglSwapIntervalEXT = NULL;

PFNGLDELETEBUFFERSPROC _glDeleteBuffers = NULL;
PFNGLDELETEVERTEXARRAYSPROC _glDeleteVertexArrays = NULL;

PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormatARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB = NULL;

PFNGLGETSHADERIVPROC _glGetShaderiv = NULL;
PFNGLGETPROGRAMIVPROC _glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC _glGetShaderInfoLog = NULL;
PFNGLGETPROGRAMINFOLOGPROC _glGetProgramInfoLog = NULL;
PFNGLDEBUGMESSAGECALLBACKPROC _glDebugMessageCallback = NULL;

static void glPlatformLoad(GLEWloadproc load)
{
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
}

void loadPFN(GLEWloadproc load)
{
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");

	glCreateTextures = (PFNGLCREATETEXTURESPROC)load("glCreateTextures");
	glTexParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)load("glTexParameterfv");
	glTexParameteri = (PFNGLTEXTUREPARAMETERIPROC)load("glTexParameteri");

	glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
	glDrawArrays = (PFNGLDRAWARRAYSEXTPROC)load("glDrawArrays");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
	glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
	glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
	glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
	glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
	glCreateBuffers = (PFNGLCREATEBUFFERSPROC)load("glCreateBuffers");

	glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)load("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)load("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC)load("glUniform4f");
	glGetUniformLocation =  (PFNGLGETUNIFORMLOCATIONARBPROC)load("glGetUniformLocation");

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)load("glValidateProgram");
	glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)load("glCreateVertexArrays");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");

	glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetShaderInfoLog");
	glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)load("glDebugMessageCallback");
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