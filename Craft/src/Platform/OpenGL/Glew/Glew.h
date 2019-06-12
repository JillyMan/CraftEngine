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

#define GL_ARRAY_BUFFER						0x8892
#define GL_STREAM_DRAW						0x88E0
#define GL_STATIC_DRAW						0x88E4
#define GL_DYNAMIC_DRAW						0x88E8
#define GL_FRAGMENT_SHADER					0x8B30
#define GL_VERTEX_SHADER					0x8B31
#define GL_COMPILE_STATUS					0x8B81

//-----------begin defines functions---------

GLAPI PFNGLCREATEPROGRAMPROC _glCreateProgram;
GLAPI PFNGLCREATEBUFFERSPROC _glCreateBuffers;
GLAPI PFNGLCREATEVERTEXARRAYSPROC _glCreateVertexArrays;

GLAPI PFNGLBINDBUFFERPROC _glBindBuffer;
GLAPI PFNGLBUFFERDATAPROC _glBufferData;
GLAPI PFNGLBINDVERTEXARRAYPROC _glBindVertexArray;

GLAPI PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray;

GLAPI PFNGLCREATESHADERPROC _glCreateShader;
GLAPI PFNGLSHADERSOURCEPROC _glShaderSource;
GLAPI PFNGLCOMPILESHADERPROC _glCompileShader;
GLAPI PFNGLATTACHSHADERPROC _glAttachShader;
GLAPI PFNGLLINKPROGRAMPROC _glLinkProgram;
GLAPI PFNGLDELETESHADERPROC _glDeleteShader;
GLAPI PFNGLUSEPROGRAMPROC _glUseProgram;

GLAPI  PFNGLDRAWARRAYSEXTPROC  _glDrawArraysEXT;

GLAPI PFNGLGETSHADERIVPROC _glGetShaderiv;
GLAPI PFNGLGENBUFFERSPROC _glGenBuffers;
GLAPI PFNWGLSWAPINTERVALEXTPROC _glSwapIntervalEXT;

GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB;

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
#define glDrawArraysEXT						_glDrawArraysEXT 
#define glSwapIntervalEXT					_glSwapIntervalEXT

#ifdef _WIN32
#define wglCreateContextAttribsARB _wglCreateContextAttribsARB
#endif

//-----------end defines functions---------

typedef void* (*GLEWloadproc)(const char *name);
GLAPI void glewLoadGLLoader(GLEWloadproc);

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE glewGetProcAddressPtr;
int glLoad();
