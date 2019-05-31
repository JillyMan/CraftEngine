#pragma once

#include "crpch.h"

#ifdef CRAFT_PLATFORM_WINDOWS
#ifdef CRAFT_DINAMIC_LINK
	#ifdef CRAFT_BUILD_DLL
		#define CRAFT_API __declspec(dllexport)
	#else		
		#define CRAFT_API __declspec(dllimport)
	#endif
#else
	#define CRAFT_API
#endif
#else
	#error Craft one support Windows
#endif

#define BIT(x) (1 << x)