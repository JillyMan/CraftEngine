#include "crpch.h"
#include "Craft/Graphics/Window.h"

EXTERN_C IMAGE_DOS_HEADER	__ImageBase;

#define HINS_THISCOMPONENT ((HINSTANCE)&__ImageBase)

namespace Craft {

	HINSTANCE HInstance;

	bool Window::PlatformInit()
	{
		HInstance = HINS_THISCOMPONENT;

		return true;
	}

	void Window::PlatformUpdate()
	{

	}

	void Window::PlatformToogleFullScreenMode()
	{

	}
}