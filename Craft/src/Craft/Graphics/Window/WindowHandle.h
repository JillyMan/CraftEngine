#pragma once

#include "Craft\Core.h"

#ifdef CRAFT_PLATFORM_WINDOWS
	struct HWND__;
	typedef HWND__* WindowHandle;
#else
	typedef void* WindowHandle;
#endif