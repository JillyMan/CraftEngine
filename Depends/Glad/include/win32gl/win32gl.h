#ifndef __win32_gl_h_
#define __win32_gl_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "glad/glad.h"
#include "wglext/wglext.h"

	GLAPI int win32_gl_load();

	GLAPI PFNWGLSWAPINTERVALEXTPROC	_wglSwapIntervalEXT;
	GLAPI PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormatARB;
	GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC	_wglCreateContextAttribsARB;

#define wglSwapIntervalEXT				_wglSwapIntervalEXT
#define wglChoosePixelFormatARB			_wglChoosePixelFormatARB
#define wglCreateContextAttribsARB		_wglCreateContextAttribsARB

#endif

#ifdef __cplusplus
}
#endif