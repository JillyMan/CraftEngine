#pragma once

#include <gl\GL.h>
#include <gl\GLext.h>
#include <gl\WGLext.h>

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GL_STATIC_LIB
# if defined(GLEW_GLAPI_EXPORT)
#  if defined(_WIN32) || defined(__CYGWIN__)
#   if defined(GLAPI_EXPORT_BUILD)
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllexport)) extern
#    else
#     define GLAPI __declspec(dllexport) extern
#    endif
#   else
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllimport)) extern
#    else
#     define GLAPI __declspec(dllimport) extern
#    endif
#   endif
#  elif defined(__GNUC__) && defined(GLAPI_EXPORT_BUILD)
#   define GLAPI __attribute__ ((visibility ("default"))) extern
#  else
#   define GLAPI extern
#  endif
# else
#  define GLAPI extern
# endif
#endif

typedef GLvoid (APIENTRYP PFNGLDELETETEXTUREPROC) (GLsizei n, const GLuint * textures);
typedef GLvoid (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
typedef GLvoid (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data);

//-----------begin defines functions---------

GLAPI PFNGLGENBUFFERSPROC					_glGenBuffers;
GLAPI PFNGLCREATEPROGRAMPROC				_glCreateProgram;
GLAPI PFNGLCREATEBUFFERSPROC				_glCreateBuffers;
GLAPI PFNGLCREATEVERTEXARRAYSPROC			 _glCreateVertexArrays;

GLAPI PFNGLBINDBUFFERPROC					_glBindBuffer;
GLAPI PFNGLBUFFERDATAPROC					_glBufferData;
GLAPI PFNGLBINDVERTEXARRAYPROC				_glBindVertexArray;

GLAPI PFNGLVERTEXATTRIBPOINTERPROC			_glVertexAttribPointer;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC		_glEnableVertexAttribArray;

GLAPI PFNGLDELETEVERTEXARRAYSPROC			_glDeleteVertexArrays;
GLAPI PFNGLDELETEBUFFERSPROC				_glDeleteBuffers;

//-Shader
GLAPI PFNGLCREATESHADERPROC					_glCreateShader;
GLAPI PFNGLSHADERSOURCEPROC					_glShaderSource;
GLAPI PFNGLCOMPILESHADERPROC				_glCompileShader;
GLAPI PFNGLATTACHSHADERPROC					_glAttachShader;
GLAPI PFNGLLINKPROGRAMPROC					_glLinkProgram;
GLAPI PFNGLDELETESHADERPROC					_glDeleteShader;
GLAPI PFNGLUSEPROGRAMPROC					_glUseProgram;
GLAPI PFNGLDELETEPROGRAMPROC				_glDeleteProgram;

GLAPI PFNGLGETUNIFORMLOCATIONARBPROC		_glGetUniformLocation;
GLAPI PFNGLUNIFORM1FPROC					_glUniform1f;
GLAPI PFNGLUNIFORM2FPROC					_glUniform2f;
GLAPI PFNGLUNIFORM3FPROC					_glUniform3f;
GLAPI PFNGLUNIFORM4FPROC					_glUniform4f;

GLAPI PFNGLVALIDATEPROGRAMPROC				_glValidateProgram;
GLAPI PFNGLGETSHADERIVPROC					_glGetShaderiv;
//-----

GLAPI PFNGLDRAWARRAYSEXTPROC				_glDrawArraysEXT;
GLAPI PFNGLDRAWELEMENTSPROC					_glDrawElements;

GLAPI PFNWGLSWAPINTERVALEXTPROC				_wglSwapIntervalEXT;
GLAPI PFNWGLCHOOSEPIXELFORMATARBPROC		_wglChoosePixelFormatARB;
GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC		_wglCreateContextAttribsARB;

//-Debug
GLAPI PFNGLDEBUGMESSAGECALLBACKPROC			_glDebugMessageCallback;
GLAPI PFNGLGETSHADERIVPROC					_glGetShaderiv;
GLAPI PFNGLGETPROGRAMIVPROC					_glGetProgramiv;
GLAPI PFNGLGETSHADERINFOLOGPROC				_glGetShaderInfoLog;
GLAPI PFNGLGETPROGRAMINFOLOGPROC			_glGetProgramInfoLog;
//----

//-Textures
GLAPI PFNGLTEXIMAGE2DPROC					_glTexImage2D;
GLAPI PFNGLTEXTUREPARAMETERIPROC			_glTextureParameteri;
GLAPI PFNGLDELETETEXTUREPROC				_glDeleteTexture;
GLAPI PFNGLCREATETEXTURESPROC				_glCreateTextures;
GLAPI PFNGLTEXTUREPARAMETERFVPROC			_glTextureParameterfv;
GLAPI PFNGLGENERATEMIPMAPPROC				_glGenerateMipmap;
//-----

#define glDebugMessageCallback				_glDebugMessageCallback
#define glBindVertexArray					_glBindVertexArray
#define glCreateShader						_glCreateShader
#define glShaderSource						_glShaderSource
#define glCompileShader						_glCompileShader
#define glCreateProgram						_glCreateProgram
#define glAttachShader						_glAttachShader
#define glLinkProgram						_glLinkProgram
#define glDeleteShader						_glDeleteShader
#define glCreateVertexArrays				_glCreateVertexArrays
#define glCreateBuffers						_glCreateBuffers
#define glBindBuffer						_glBindBuffer
#define glBufferData						_glBufferData
#define glVertexAttribPointer				_glVertexAttribPointer
#define glEnableVertexAttribArray			_glEnableVertexAttribArray
#define glUseProgram						_glUseProgram
#define glDeleteProgram						_glDeleteProgram
#define glDrawArrays						_glDrawArraysEXT 
#define glDrawElements						_glDrawElements
#define glDeleteVertexArrays				_glDeleteVertexArrays
#define glDeleteBuffers						_glDeleteBuffers

#define glUniform1f							_glUniform1f
#define glUniform2f							_glUniform2f
#define glUniform3f							_glUniform3f
#define glUniform4f							_glUniform4f
#define glGetUniformLocation				_glGetUniformLocation

#define glValidateProgram					_glValidateProgram
#define glGetShaderiv						_glGetShaderiv
#define glGetProgramiv						_glGetProgramiv
#define glGetShaderInfoLog					_glGetShaderInfoLog
#define glGetProgramInfoLog					_glGetProgramInfoLog

#define glTexImage2D						_glTexImage2D
#define glTextureParameteri					_glTextureParameteri
#define glTextureParameterfv				_glTextureParameterfv
#define glGenerateMipmap					_glGenerateMipmap
#define glCreateTextures					_glCreateTextures
//------

#ifdef _WIN32
	#define wglSwapIntervalEXT				_wglSwapIntervalEXT
	#define wglChoosePixelFormatARB			_wglChoosePixelFormatARB
	#define wglCreateContextAttribsARB		_wglCreateContextAttribsARB
#endif

//-----------end defines functions---------

typedef void* (*GLEWloadproc)(const char *name);
GLAPI void glewLoadGLLoader(GLEWloadproc);

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE glewGetProcAddressPtr;
int pfnGLLoad();