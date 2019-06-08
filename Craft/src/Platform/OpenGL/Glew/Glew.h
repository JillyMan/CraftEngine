#pragma once

#include <gl\GL.h>

#ifndef APIENTRY
	#define APIENTRY
#endif

#ifndef APIENTRYP
	#define APIENTRYP APIENTRY *
#endif

#ifndef GL_STATIC_LIB
# if defined(GLAD_GLAPI_EXPORT)
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

typedef int* GLintptr;
typedef GLsizei* GLsizeiptr;


typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GLAPI PFNGLBINDVERTEXBUFFERPROC craft_glBindVertexBuffer;
#define glBindVertexBuffer glew_glBindVertexBuffer

typedef void (APIENTRYP PFNGLGENBUFFERS)(GLsizei, GLuint*);
GLAPI PFNGLGENBUFFERS glew_glGenBuffers;
#define glGenBuffers glew_glGenBuffers;

typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glew_glBindBuffer;
#define glBindBuffer glew_glBindBuffer;

typedef void (APIENTRYP PFNGLBUFFERDATA) (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
GLAPI PFNGLBUFFERDATA glew_glBufferData;
#define glBufferData glew_glBufferData;

void glewInit();