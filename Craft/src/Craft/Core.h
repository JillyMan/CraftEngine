#pragma once

#include "Types.h"

#ifdef CRAFT_PLATFORM_WINDOWS
	#ifdef CRAFT_BUILD_DLL
		#define CRAFT_API __declspec(dllexport)
	#else		
		#define CRAFT_API __declspec(dllimport)
	#endif
#else
	#error Craft one support Windows
#endif