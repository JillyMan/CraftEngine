#pragma once

#include <gl\GL.h>

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

typedef char GLchar;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

#define GL_ARRAY_BUFFER						0x8892
#define GL_STREAM_DRAW						0x88E0
#define GL_STATIC_DRAW						0x88E4
#define GL_DYNAMIC_DRAW						0x88E8
#define GL_FRAGMENT_SHADER					0x8B30
#define GL_VERTEX_SHADER					0x8B31
#define GL_COMPILE_STATUS					0x8B81


//-----------begin defines functions---------

typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
GLAPI PFNGLGETSHADERIVPROC glGetShaderiv;

typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
GLAPI PFNGLCOMPILESHADERPROC glCompileShader;

typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
GLAPI PFNGLSHADERSOURCEPROC glShaderSource;

typedef GLuint(APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
GLAPI PFNGLCREATESHADERPROC glCreateShader;

typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
GLAPI PFNGLBUFFERDATAPROC glBufferData;

typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GLAPI PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
GLAPI PFNGLGENBUFFERSPROC glGenBuffers;

typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glBindBuffer;

typedef	bool(APIENTRY *PFNWGLSWAPINTERVALFARPROC)(GLint);
GLAPI PFNWGLSWAPINTERVALFARPROC glSwapInterval;

int glewLoadGL();

typedef void* (*GLEWloadproc)(const char *name);
GLAPI void glewLoadGLLoader(GLEWloadproc);

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE glewGetProcAddressPtr;

//-----------end defines functions---------