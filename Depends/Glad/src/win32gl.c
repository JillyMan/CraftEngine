#include "win32gl/win32gl.h"

static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

PFNWGLSWAPINTERVALEXTPROC _wglSwapIntervalEXT = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormatARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB = NULL;

static int open_gl(void) {
	libGL = LoadLibraryW(L"opengl32.dll");
	if (libGL != NULL) {
		void (*tmp)(void);
		tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
		gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)tmp;
		return gladGetProcAddressPtr != NULL;
	}
	return 0;
}

static void* get_proc(const char* namez) {
	void* result = NULL;
	if (libGL == NULL) return NULL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
	if (gladGetProcAddressPtr != NULL) {
		result = gladGetProcAddressPtr(namez);
	}
#endif
	if (result == NULL) {
#if defined(_WIN32) || defined(__CYGWIN__)
		result = (void*)GetProcAddress((HMODULE)libGL, namez);
#else
		result = dlsym(libGL, namez);
#endif
	}

	return result;
}


static void loadwgl(GLADloadproc load) {
	_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
	_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
}

int win32_gl_load()
{
	int status = gladLoadGL() && open_gl();
	loadwgl(&get_proc);
	return status;
}


