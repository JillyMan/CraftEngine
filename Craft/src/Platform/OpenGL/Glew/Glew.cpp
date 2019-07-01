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
PFNGLUNIFORM1IPROC					_glUniform1i = NULL;
PFNGLUNIFORM2IPROC					_glUniform2i = NULL;
PFNGLUNIFORM3IPROC					_glUniform3i = NULL;
PFNGLUNIFORM4IPROC					_glUniform4i = NULL;
PFNGLUNIFORM1FPROC					_glUniform1f = NULL;
PFNGLUNIFORM2FPROC					_glUniform2f = NULL;
PFNGLUNIFORM3FPROC					_glUniform3f = NULL;
PFNGLUNIFORM4FPROC					_glUniform4f = NULL;

PFNGLACTIVETEXTUREPROC				_glActiveTexture = NULL;
PFNGLCREATETEXTURESPROC				_glCreateTextures = NULL;
PFNGLTEXTUREPARAMETERFVPROC			_glTextureParameterfv = NULL;
PFNGLTEXTUREPARAMETERIPROC			_glTextureParameteri = NULL;
PFNGLGENERATEMIPMAPPROC				_glGenerateMipmap = NULL;
PFNGLTEXIMAGE2DPROC					_glTexImage2D = NULL;

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

	glTexImage2D = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
	glCreateTextures = (PFNGLCREATETEXTURESPROC)load("glCreateTextures");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");
	glTextureParameteri =  (PFNGLTEXTUREPARAMETERIPROC)load("glTextureParameteri");
	glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)load("glTextureParameterfv");

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

	glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)load("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC)load("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC)load("glUniform4i");
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